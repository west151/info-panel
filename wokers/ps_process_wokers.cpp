#include "ps_process_wokers.h"
#include <QTimer>
#include <QMetaEnum>

#ifdef QT_DEBUG
#include <QDebug>
#endif

template<typename QEnum>
QString QtEnumToString (const QEnum value)
{
  return QString(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

ps_process_wokers::ps_process_wokers(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this,
            &ps_process_wokers::slot_run_program);
}

void ps_process_wokers::slot_start_workers()
{
    m_timer->start(1000);
}

void ps_process_wokers::slot_ready_read_standard_output()
{
    QProcess *ptr_process = dynamic_cast<QProcess *>(sender());

    while (ptr_process->canReadLine()) {
        const QString line = QString::fromLocal8Bit(ptr_process->readLine());
        parser_line(line);
    }
}

void ps_process_wokers::slot_error(QProcess::ProcessError error)
{
#ifdef QT_DEBUG
    qDebug() << tr("error:") << QtEnumToString(error);
#endif
}

void ps_process_wokers::slot_finished(int exit_code, QProcess::ExitStatus exit_status)
{
    QProcess *ptr_process = dynamic_cast<QProcess *>(sender());

#ifdef QT_DEBUG
    qDebug() << tr("finished (%1):").arg(ptr_process->objectName()) << exit_code << QtEnumToString(exit_status);
#endif
}

void ps_process_wokers::slot_run_program()
{
    QObject *parent = new QObject;
    QStringList arg;
    QString program = "ps";
    arg << "aux";
    QProcess *ptr_process = new QProcess(parent);
    ptr_process->setObjectName(program);

    connect(ptr_process, &QProcess::readyReadStandardOutput,
            this, &ps_process_wokers::slot_ready_read_standard_output);

    connect(ptr_process, &QProcess::errorOccurred,
            this, &ps_process_wokers::slot_error);

    connect(ptr_process, &QProcess::finished,
            this, &ps_process_wokers::slot_finished);

    ptr_process->start(program, arg);

//    if(ptr_process->state() == QProcess::NotRunning)
//    {
//#ifdef QT_DEBUG
//        qDebug() << ptr_process->errorString();
//        qDebug() << tr("environment:") << QProcess::systemEnvironment();
//#endif
//    }else{
//#ifdef QT_DEBUG
//        qDebug() << tr("PID:") << ptr_process->pid() << ptr_process->processId() << ptr_process->program();
//#endif
//    }
}

void ps_process_wokers::parser_line(const QString &value)
{
    QString tmp_line(value);
    tmp_line.remove("\n");

    if(!value.contains("USER"))
    {
        const QList<QString> lines = tmp_line.simplified().split(' ');

        process_info info;
        info.set_user(lines.at(0));
        info.set_pid(lines.at(1).toInt(0));
        info.set_cpu_usage(lines.at(2).toFloat(0));
        info.set_mem_usage(lines.at(3).toFloat(0));
        info.set_command(lines.at(10));

        if(info.cpu_usage() > 5)
            emit signal_process_info_data(info);

//#ifdef QT_DEBUG
//        qDebug() << lines.at(0)     // USER (string)
//                 << lines.at(1)     // PID  (int)
//                 << lines.at(2)     // %CPU (0.0)
//                 << lines.at(3)     // %MEM (0.0)
//                 << lines.at(10);   // COMMAND (string)
//#endif
    }
}
