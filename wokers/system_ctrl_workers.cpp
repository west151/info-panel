#include "system_ctrl_workers.h"

#include <QMetaEnum>
#include <QStringList>

#ifdef QT_DEBUG
#include <QDebug>
#endif

template<typename QEnum>
QString QtEnumToString (const QEnum value)
{
  return QString(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

system_ctrl_workers::system_ctrl_workers(QObject *parent) : QObject(parent)
{

}

void system_ctrl_workers::slot_run_ctrl(const sys_ctrl_cmd &cmd)
{

    QObject *parent = new QObject;
    QString program;
    QStringList arguments;

    if(cmd == sys_ctrl_cmd::reboot_system)
        program = "reboot";

    if(cmd == sys_ctrl_cmd::shutdown_system){
        program = "shutdown";
        arguments << "-h" << "now";
    }

    QProcess *ptr_process = new QProcess(parent);
    ptr_process->setObjectName(program);

//    if(!arguments.isEmpty())
//        ptr_process->setArguments(arguments);

    connect(ptr_process, &QProcess::started,
            this, &system_ctrl_workers::slot_started );

    connect(ptr_process, &QProcess::errorOccurred,
            this, &system_ctrl_workers::slot_error);

    connect(ptr_process, &QProcess::finished,
            this, &system_ctrl_workers::slot_finished);

    ptr_process->start(program, arguments);

    if(ptr_process->state() == QProcess::NotRunning)
    {
#ifdef QT_DEBUG
        qDebug() << ptr_process->errorString();
        qDebug() << tr("environment:") << QProcess::systemEnvironment();
#endif
    }else{
#ifdef QT_DEBUG
        qDebug() << tr("pid:") << ptr_process->pid() << ptr_process->processId() << ptr_process->program();
        qDebug() << tr("programs:") << ptr_process->program() << ptr_process->arguments();
#endif
    }
}

void system_ctrl_workers::slot_started()
{

}

void system_ctrl_workers::slot_error(QProcess::ProcessError error)
{
#ifdef QT_DEBUG
    qDebug() << tr("error:") << QtEnumToString(error);
#endif
}

void system_ctrl_workers::slot_finished(int exit_code, QProcess::ExitStatus exit_status)
{
    QProcess *ptr_process = dynamic_cast<QProcess *>(sender());

#ifdef QT_DEBUG
    qDebug() << tr("finished (%1):").arg(ptr_process->objectName()) << exit_code << QtEnumToString(exit_status);
#endif
}
