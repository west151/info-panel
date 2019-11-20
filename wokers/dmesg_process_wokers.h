#ifndef DMESG_PROCESS_WOKERS_H
#define DMESG_PROCESS_WOKERS_H

#include <QObject>
#include <QProcess>

#include "model/message_log.h"

class dmesg_process_wokers : public QObject
{
    Q_OBJECT
public:
    explicit dmesg_process_wokers(QObject *parent = nullptr);

signals:
    void signal_message_log_data(const message_log &);
    void signal_vector_message_log_data(const QVector<message_log> &);

public slots:
    void slot_run_dmesg();

private slots:
    void slot_started();
    void slot_ready_read_standard_output();
    void slot_error(QProcess::ProcessError error);
    void slot_finished(int exit_code, QProcess::ExitStatus exit_status);

private:
    void parser_line(const QString &);
};

#endif // DMESG_PROCESS_WOKERS_H
