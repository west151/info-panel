#include "user_interface.h"

#include <QTimer>

user_interface::user_interface(QObject *parent) : QObject(parent),
    m_timer(new QTimer(this))
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

void user_interface::slot_system_time_update()
{
    m_system_time = QDateTime::currentDateTime();

    emit signal_time_changed();
}
