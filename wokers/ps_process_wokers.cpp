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
    m_min_cpu_usage = 1;
    m_pid_current = 0;

    connect(m_timer, &QTimer::timeout, this,
            &ps_process_wokers::slot_run_program);
}

void ps_process_wokers::slot_start_workers()
{
    m_timer->setInterval(2000);
    m_timer->start();
}

void ps_process_wokers::slot_current_pid(const int &value)
{
    m_pid_current = value;
}

void ps_process_wokers::slot_min_cpu_usage(const float &value)
{
    m_min_cpu_usage = value;
}

void ps_process_wokers::slot_ready_read_standard_output()
{
    QProcess *ptr_process = dynamic_cast<QProcess *>(sender());

    QVector<process_info> result;

    while (ptr_process->canReadLine()) {
        const QString line = QString::fromLocal8Bit(ptr_process->readLine());
        const auto data = parser_line(line);

        if(data.cpu_usage() >= m_min_cpu_usage)
        {
            if(m_pid_current == 0)
            {
                result.append(data);
                m_result_sending.append(data);
            }else{
                if(data.pid() == m_pid_current)
                {
                    result.append(data);
                    m_result_sending.append(data);
                }
            }
        }

        //if((m_pid_current != 0)||(data.pid()==m_pid_current)){
//            if((data.pid() != 0)&&(data.cpu_usage() >= m_min_cpu_usage)){
//                result.append(data);
//                m_result_sending.append(data);
//            }
        //}
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

    if(exit_status == QProcess::CrashExit){
#ifdef QT_DEBUG
        qDebug() << tr("finished (%1):").arg(ptr_process->objectName()) << exit_code << QtEnumToString(exit_status);
#endif
    }

    if(exit_status == QProcess::NormalExit)
        emit signal_process_info_data(m_result_sending);

    m_result_sending.clear();
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

    if(ptr_process->state() == QProcess::NotRunning)
    {
#ifdef QT_DEBUG
        qDebug() << ptr_process->errorString();
        qDebug() << tr("environment:") << ptr_process->systemEnvironment();
#endif
    }else{
#ifdef QT_DEBUG
        qDebug() << tr("PID:") << ptr_process->pid() << ptr_process->processId() << ptr_process->program();
#endif
    }
}

process_info ps_process_wokers::parser_line(const QString &value) const
{
    process_info info;
    QString tmp_line(value);
    tmp_line.remove("\n");

    if(!value.contains("USER"))
    {
        const QStringList lines = tmp_line.simplified().split(' ');

        info.set_user(lines.at(0).trimmed());
        info.set_pid(lines.at(1).toInt(0));
        info.set_cpu_usage(lines.at(2).toFloat(0));
        info.set_mem_usage(lines.at(3).toFloat(0));
        info.set_command(lines.at(10));

        //#ifdef QT_DEBUG
        //        qDebug() << lines.at(0)     // USER (string)
        //                 << lines.at(1)     // PID  (int)
        //                 << lines.at(2)     // %CPU (0.0)
        //                 << lines.at(3)     // %MEM (0.0)
        //                 << lines.at(10);   // COMMAND (string)
        //#endif
    }

    return info;
}
