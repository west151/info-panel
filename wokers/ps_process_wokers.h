#ifndef PS_PROCESS_WOKERS_H
#define PS_PROCESS_WOKERS_H

#include <QObject>
#include <QProcess>

#include "model/process_info.h"

class QTimer;

class ps_process_wokers : public QObject
{
    Q_OBJECT
public:
    explicit ps_process_wokers(QObject *parent = nullptr);

signals:
    void signal_process_info_data(const process_info &);

public slots:
    void slot_start_workers();

private slots:
    void slot_ready_read_standard_output();
    void slot_error(QProcess::ProcessError error);
    void slot_finished(int exit_code, QProcess::ExitStatus exit_status);
    void slot_run_program();

private:
    QTimer *m_timer;
    void parser_line(const QString &);

};

#endif // PS_PROCESS_WOKERS_H
