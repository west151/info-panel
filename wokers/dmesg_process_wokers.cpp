#include "dmesg_process_wokers.h"

#include <QMetaEnum>

#ifdef QT_DEBUG
#include <QDebug>
#endif

template<typename QEnum>
QString QtEnumToString (const QEnum value)
{
  return QString(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

dmesg_process_wokers::dmesg_process_wokers(QObject *parent) : QObject(parent)
{

}

void dmesg_process_wokers::slot_error(QProcess::ProcessError error)
{
#ifdef QT_DEBUG
    qDebug() << tr("error:") << QtEnumToString(error);
#endif
}

void dmesg_process_wokers::slot_finished(int exit_code, QProcess::ExitStatus exit_status)
{
    QProcess *ptr_process = dynamic_cast<QProcess *>(sender());

#ifdef QT_DEBUG
    qDebug() << tr("finished (%1):").arg(ptr_process->objectName()) << exit_code << QtEnumToString(exit_status);
#endif
}

void dmesg_process_wokers::slot_ready_read_standard_output()
{
    QProcess *ptr_process = dynamic_cast<QProcess *>(sender());

    while (ptr_process->canReadLine()) {
        const QString line = QString::fromLocal8Bit(ptr_process->readLine());
        parser_line(line);
    }
}

void dmesg_process_wokers::slot_run_dmesg()
{
    QObject *parent = new QObject;
    QString program = "dmesg";
    QProcess *ptr_process = new QProcess(parent);
    ptr_process->setObjectName(program);

    connect(ptr_process, &QProcess::readyReadStandardOutput,
            this, &dmesg_process_wokers::slot_ready_read_standard_output);

    connect(ptr_process, &QProcess::errorOccurred,
            this, &dmesg_process_wokers::slot_error);

    connect(ptr_process, &QProcess::finished,
            this, &dmesg_process_wokers::slot_finished);

    ptr_process->start(program);

    if(ptr_process->state() == QProcess::NotRunning)
    {
#ifdef QT_DEBUG
        qDebug() << ptr_process->errorString();
        qDebug() << tr("environment:") << QProcess::systemEnvironment();
#endif
    }else{
#ifdef QT_DEBUG
        qDebug() << tr("pid:") << ptr_process->pid() << ptr_process->processId() << ptr_process->program();
#endif
    }
}

void dmesg_process_wokers::parser_line(const QString &value)
{
    QString tmp_line(value);
    tmp_line.remove("\n");

    int start = tmp_line.indexOf("[");
    int end = tmp_line.indexOf("]");

    message_log data;
    data.set_message_log_id(tmp_line.mid(start, end + 1));
    data.set_message_log_text(tmp_line.remove(start, end + 1).trimmed());

    emit signal_message_log_data(data);
}
