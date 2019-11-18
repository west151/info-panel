#ifndef CORE_SWEEP_REMOTE_CONTROL_H
#define CORE_SWEEP_REMOTE_CONTROL_H

#include <QObject>
#include <QPointer>
#include <QQmlApplicationEngine>

class user_interface;
class system_info_model;
class system_info_workers;
class message_log_model;
class dmesg_process_wokers;

class core_info_panel : public QObject
{
    Q_OBJECT
public:
    explicit core_info_panel(QObject *parent = nullptr);

    // read file settings
    bool initialization();
    // program launch
    void program_launch(bool is_init_state);

signals:
    void signal_start();

public slots:

private:
    user_interface* ptr_user_interface {Q_NULLPTR};
    system_info_model* ptr_system_info_model {Q_NULLPTR};
    message_log_model* ptr_message_log_model {Q_NULLPTR};

    system_info_workers* ptr_system_info_workers {Q_NULLPTR};
    QPointer<QThread> ptr_system_info_thread;

    dmesg_process_wokers* ptr_dmesg_process_wokers {Q_NULLPTR};
    QPointer<QThread> ptr_dmesg_process_thread;

    QQmlApplicationEngine* ptr_engine {Q_NULLPTR};
};

#endif // CORE_SWEEP_REMOTE_CONTROL_H
