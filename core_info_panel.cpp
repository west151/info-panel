#include "core_info_panel.h"

#include <QString>
#include <QQmlContext>
#include <QThread>
#include <QTimer>

#include "model/info_panel_model.h"
#include "model/system_info_model.h"
#include "wokers/system_info_workers.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

core_info_panel::core_info_panel(QObject *parent) : QObject(parent),
    ptr_info_panel_model(new info_panel_model(this)),
    ptr_system_info_model(new system_info_model(this))
{
    qRegisterMetaType<system_info>("system_info");
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

    return status;
}

void core_info_panel::program_launch(bool is_init_state)
{
    ptr_engine = new QQmlApplicationEngine(this);

    QQmlContext *context = ptr_engine->rootContext();
    context->setContextProperty("info_panel_model", ptr_info_panel_model);
    context->setContextProperty("system_info_model", ptr_system_info_model);

    ptr_engine->load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    ptr_info_panel_model->start();

    QTimer::singleShot(1000, this, &core_info_panel::signal_start);
}
