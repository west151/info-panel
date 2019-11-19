#ifndef SYSTEM_CTRL_WORKERS_H
#define SYSTEM_CTRL_WORKERS_H

#include <QObject>
#include <QProcess>

#include "shared/local_const.h"

class system_ctrl_workers : public QObject
{
    Q_OBJECT
public:
    explicit system_ctrl_workers(QObject *parent = nullptr);

public slots:
    void slot_run_ctrl(const sys_ctrl_cmd &);

private slots:
    void slot_started();
    void slot_error(QProcess::ProcessError error);
    void slot_finished(int exit_code, QProcess::ExitStatus exit_status);
};

#endif // SYSTEM_CTRL_WORKERS_H
