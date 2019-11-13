#include "info_panel_model.h"

#include <QTimer>

info_panel_model::info_panel_model(QObject *parent) : QObject(parent),
    m_timer(new QTimer(this))
{
    connect(m_timer, &QTimer::timeout,
            this, &info_panel_model::slot_system_time_update);

    // default datetime
    m_system_time = QDateTime::currentDateTime();
}

void info_panel_model::start()
{
    m_timer->start(1000);
}

QString info_panel_model::system_time() const
{
    return m_system_time.toString("hh:mm:ss dd.MM.yyyy (t)");
}

void info_panel_model::slot_system_time_update()
{
    m_system_time = QDateTime::currentDateTime();

    emit signal_time_changed();
}
