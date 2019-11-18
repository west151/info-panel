#include "core_info_panel.h"

#include <QString>
#include <QQmlContext>
#include <QThread>
#include <QTimer>

#include "model/user_interface.h"
#include "model/system_info_model.h"
#include "model/message_log_model.h"
#include "wokers/system_info_workers.h"
#include "wokers/dmesg_process_wokers.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

core_info_panel::core_info_panel(QObject *parent) : QObject(parent),
    ptr_user_interface(new user_interface(this)),
    ptr_system_info_model(new system_info_model(this)),
    ptr_message_log_model(new message_log_model(this))
{
    qRegisterMetaType<system_info>("system_info");
    qRegisterMetaType<message_log>("message_log");
}

bool core_info_panel::initialization()
{
    bool status(false);

    ptr_system_info_workers = new system_info_workers;
    ptr_system_info_thread = new QThread;
    ptr_system_info_workers->moveToThread(ptr_system_info_thread);

    connect(ptr_system_info_workers, &system_info_workers::signal_result_system_info,
            ptr_system_info_model, &system_info_model::add_data_to_model);

    connect(this, &core_info_panel::signal_start,
            ptr_system_info_workers, &system_info_workers::slot_start_workers);

    ptr_system_info_thread->start();

    //
    ptr_dmesg_process_wokers = new dmesg_process_wokers;
    ptr_dmesg_process_thread = new QThread;
    ptr_dmesg_process_wokers->moveToThread(ptr_dmesg_process_thread);

    connect(ptr_dmesg_process_wokers, &dmesg_process_wokers::signal_message_log_data,
            ptr_message_log_model, &message_log_model::slot_add_data_to_model);

    connect(ptr_user_interface, &user_interface::signal_run_dmesg,
            ptr_dmesg_process_wokers, &dmesg_process_wokers::slot_run_dmesg);

    ptr_dmesg_process_thread->start();

    return status;
}

void core_info_panel::program_launch(bool is_init_state)
{
    ptr_engine = new QQmlApplicationEngine(this);

    QQmlContext *context = ptr_engine->rootContext();
    context->setContextProperty("user_interface", ptr_user_interface);
    context->setContextProperty("system_info_model", ptr_system_info_model);
    context->setContextProperty("dmesg_process_wokers", ptr_dmesg_process_wokers);
    context->setContextProperty("message_log_model", ptr_message_log_model);

    ptr_engine->load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    ptr_user_interface->start();

    QTimer::singleShot(1000, this, &core_info_panel::signal_start);
}
