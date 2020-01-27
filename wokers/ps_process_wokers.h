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
    void signal_process_info_data(const QVector<process_info> &);
    void signal_finished();

public slots:
    void slot_start_workers();
    void slot_current_pid(const QString &);
    void slot_min_cpu_usage(const float &);

private slots:
    void slot_ready_read_standard_output();
    void slot_error(QProcess::ProcessError error);
    void slot_finished(int exit_code, QProcess::ExitStatus exit_status);
    void slot_run_program();

private:
    QTimer *m_timer;
    float m_min_cpu_usage;
    QString m_pid_current;
    QVector<process_info> m_result_sending;

    process_info parser_line(const QString &)const;
};

#endif // PS_PROCESS_WOKERS_H
