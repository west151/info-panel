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
    Q_PROPERTY(QString scan_state READ scan_state NOTIFY signal_scan_state)
    Q_PROPERTY(bool power_state READ power_state NOTIFY signal_power_state)
public:
    explicit user_interface(QObject *parent = nullptr);

    void start();
    QString system_time()const;
    QString scan_state()const;

    bool power_state()const;

    Q_INVOKABLE void on_update_dmesg();
    Q_INVOKABLE void on_reboot_system();
    Q_INVOKABLE void on_shutdown_system();
    Q_INVOKABLE void on_change_filter_text(const QString &);
    Q_INVOKABLE void on_start_scan();
    Q_INVOKABLE void on_stop_scan();
    Q_INVOKABLE void on_power_ctrl(const bool &);

public slots:
    void slot_scan_finished();
    void slot_power_state(const bool &);

signals:
    void signal_time_changed();
    void signal_run_dmesg();
    void signal_run_ctrl(const sys_ctrl_cmd &);
    void signal_change_filter_text(const QString &);
    void signal_start_scan();
    void signal_stop_scan();
    void signal_scan_state();
    void signal_power_state();
    void signal_power_ctrl(const bool &);

private:
    QDateTime m_system_time;
    QTimer *m_timer;
    QString m_scan_state;
    bool is_power_state;

private slots:
    void slot_system_time_update();
};

#endif // USER_INTERFACE_H
