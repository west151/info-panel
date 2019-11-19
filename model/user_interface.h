#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <QObject>
#include <QDateTime>

#include "shared/local_const.h"

class QTimer;

class user_interface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString system_time READ system_time NOTIFY signal_time_changed)
public:
    explicit user_interface(QObject *parent = nullptr);

    void start();
    QString system_time()const;

    Q_INVOKABLE void on_update_dmesg();
    Q_INVOKABLE void on_reboot_system();
    Q_INVOKABLE void on_shutdown_system();

signals:
    void signal_time_changed();
    void signal_run_dmesg();
    void signal_run_ctrl(const sys_ctrl_cmd &);

private:
    QDateTime m_system_time;
    QTimer *m_timer;

private slots:
    void slot_system_time_update();
};

#endif // USER_INTERFACE_H
