#include "user_interface.h"

#include <QTimer>

#ifdef QT_DEBUG
#include <QDebug>
#endif

user_interface::user_interface(QObject *parent) : QObject(parent),
    m_timer(new QTimer(this)),
    is_power_state(false)
{
    connect(m_timer, &QTimer::timeout,
            this, &user_interface::slot_system_time_update);

    // default datetime
    m_system_time = QDateTime::currentDateTime();
}

void user_interface::start()
{
    m_timer->start(1000);
}

QString user_interface::system_time() const
{
    return m_system_time.toString("hh:mm:ss dd.MM.yyyy (t)");
}

QString user_interface::scan_state() const
{
    return m_scan_state;
}

bool user_interface::power_state() const
{
    return is_power_state;
}

void user_interface::on_update_dmesg()
{
    emit signal_run_dmesg();
}

void user_interface::on_reboot_system()
{
    emit signal_run_ctrl(sys_ctrl_cmd::reboot_system);
}

void user_interface::on_shutdown_system()
{
    emit signal_run_ctrl(sys_ctrl_cmd::shutdown_system);
}

void user_interface::on_change_filter_text(const QString &value)
{
    emit signal_change_filter_text(value);
}

void user_interface::on_start_scan()
{
    emit signal_start_scan();
}

void user_interface::on_stop_scan()
{
    emit signal_stop_scan();
}

void user_interface::on_power_ctrl(const bool &value)
{
    emit signal_power_ctrl(value);
}

void user_interface::on_min_cpu_usage(const float &value)
{
    emit signal_min_cpu_usage(value);
}

void user_interface::on_current_pid(const int &value)
{
    emit signal_current_pid(value);
}

void user_interface::slot_scan_finished()
{
    m_scan_state = "finished";

    emit signal_scan_state();
}

void user_interface::slot_power_state(const bool &value)
{
    is_power_state = value;

    emit signal_power_state();
}

void user_interface::slot_system_time_update()
{
    m_system_time = QDateTime::currentDateTime();

    emit signal_time_changed();
}
