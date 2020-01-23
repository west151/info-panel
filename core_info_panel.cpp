#include "core_info_panel.h"

#include <QString>
#include <QQmlContext>
#include <QThread>
#include <QTimer>

#include "model/user_interface.h"
#include "model/system_info_model.h"
#include "model/message_log_model.h"
#include "model/sort_filter_proxy_model.h"
#include "model/bluetooth_device_model.h"
#include "model/cpu_usage_model.h"

#include "wokers/system_info_workers.h"
#include "wokers/dmesg_process_wokers.h"
#include "wokers/system_ctrl_workers.h"
#include "wokers/bluetooth_discovery_workers.h"
#include "wokers/cpu_usage_workers.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

core_info_panel::core_info_panel(QObject *parent) : QObject(parent),
    ptr_user_interface(new user_interface(this)),
    ptr_system_info_model(new system_info_model(this)),
    ptr_message_log_model(new message_log_model(this)),
    ptr_sort_filter_proxy_model(new sort_filter_proxy_model(this)),
    ptr_bluetooth_device_model(new bluetooth_device_model(this)),
    ptr_cpu_usage_model(new cpu_usage_model(this))
{
    qRegisterMetaType<system_info>("system_info");
    qRegisterMetaType<message_log>("message_log");
    qRegisterMetaType<QVector<message_log> >("QVector<message_log>");
    qRegisterMetaType<sys_ctrl_cmd>("sys_ctrl_cmd");
    qRegisterMetaType<data_log_type>("data_log_type");
    qRegisterMetaType<bluetooth_device_info>("bluetooth_device_info");

    ptr_sort_filter_proxy_model->setSourceModel(ptr_message_log_model);    

    connect(ptr_user_interface, &user_interface::signal_change_filter_text,
            this, &core_info_panel::slot_filter_text_changed);
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

    // dmesg process
    ptr_dmesg_process_wokers = new dmesg_process_wokers;
    ptr_dmesg_process_thread = new QThread;
    ptr_dmesg_process_wokers->moveToThread(ptr_dmesg_process_thread);

    connect(ptr_dmesg_process_wokers, &dmesg_process_wokers::signal_message_log_data,
            ptr_message_log_model, &message_log_model::slot_add_data_to_model);

    connect(ptr_user_interface, &user_interface::signal_run_dmesg,
            ptr_dmesg_process_wokers, &dmesg_process_wokers::slot_run_dmesg);

    ptr_dmesg_process_thread->start();

    ptr_system_ctrl_workers = new system_ctrl_workers;
    ptr_dmesg_process_thread = new QThread;
    ptr_system_ctrl_workers->moveToThread(ptr_dmesg_process_thread);

    connect(ptr_user_interface, &user_interface::signal_run_ctrl,
            ptr_system_ctrl_workers, &system_ctrl_workers::slot_run_ctrl);

    ptr_dmesg_process_thread->start();

    // bluetooth discovery
    ptr_bluetooth_discovery_workers = new bluetooth_discovery_workers;
    ptr_bluetooth_discovery_thread = new QThread;
    ptr_bluetooth_discovery_workers->moveToThread(ptr_bluetooth_discovery_thread);

    // info
    connect(ptr_bluetooth_discovery_workers, &bluetooth_discovery_workers::signal_result_system_info,
            ptr_system_info_model, &system_info_model::add_data_to_model);

    // bluetooth device info
    connect(ptr_bluetooth_discovery_workers, &bluetooth_discovery_workers::signal_bluetooth_device_info,
            ptr_bluetooth_device_model, &bluetooth_device_model::slot_add_data_to_model);

    connect(this, &core_info_panel::signal_start,
            ptr_bluetooth_discovery_workers, &bluetooth_discovery_workers::slot_start_workers);

    // start scan
    connect(ptr_user_interface, &user_interface::signal_start_scan,
            ptr_bluetooth_discovery_workers, &bluetooth_discovery_workers::slot_start_scan);

    // stop scan
    connect(ptr_user_interface, &user_interface::signal_stop_scan,
            ptr_bluetooth_discovery_workers, &bluetooth_discovery_workers::slot_stop_scan);

    // scan finished
    connect(ptr_bluetooth_discovery_workers, &bluetooth_discovery_workers::signal_scan_finished,
            ptr_user_interface, &user_interface::slot_scan_finished);

    // power state
    connect(ptr_bluetooth_discovery_workers, &bluetooth_discovery_workers::signal_power_state,
            ptr_user_interface, &user_interface::slot_power_state);

    // power control
    connect(ptr_user_interface, &user_interface::signal_power_ctrl,
            ptr_bluetooth_discovery_workers, &bluetooth_discovery_workers::slot_power_ctrl);

    ptr_bluetooth_discovery_thread->start();

    // cpu usage
    ptr_cpu_usage_workers = new cpu_usage_workers;
    ptr_cpu_usage_thread = new QThread;
    ptr_cpu_usage_workers->moveToThread(ptr_cpu_usage_thread);

    connect(this, &core_info_panel::signal_start,
            ptr_cpu_usage_workers, &cpu_usage_workers::slot_start_workers);

    //ptr_cpu_usage_model
    connect(ptr_cpu_usage_workers, &cpu_usage_workers::signal_result_cpu_usage,
            ptr_cpu_usage_model, &cpu_usage_model::slot_add_data_to_model);

    ptr_cpu_usage_thread->start();

    return status;
}

void core_info_panel::program_launch(bool is_init_state)
{
    Q_UNUSED(is_init_state)

    ptr_engine = new QQmlApplicationEngine(this);

    QQmlContext *context = ptr_engine->rootContext();
    context->setContextProperty("user_interface", ptr_user_interface);
    context->setContextProperty("system_info_model", ptr_system_info_model);
    context->setContextProperty("message_log_model", ptr_message_log_model);
    context->setContextProperty("sort_filter_proxy_model", ptr_sort_filter_proxy_model);
    context->setContextProperty("bluetooth_device_model", ptr_bluetooth_device_model);
    context->setContextProperty("cpu_usage_model", ptr_cpu_usage_model);

    ptr_engine->load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    ptr_user_interface->start();

    QTimer::singleShot(1000, this, &core_info_panel::signal_start);
}

void core_info_panel::slot_filter_text_changed(const QString &value)
{
    QRegExp reg_exp(value.toLower(), Qt::CaseSensitive, QRegExp::FixedString);
    ptr_sort_filter_proxy_model->setFilterRegExp(reg_exp);
}
