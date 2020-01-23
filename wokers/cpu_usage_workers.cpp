#include "cpu_usage_workers.h"
#include <QFile>
#include <QTimer>
#include <QTextStream>

#ifdef QT_DEBUG
#include <QDebug>
#endif

cpu_usage_workers::cpu_usage_workers(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout, this, &cpu_usage_workers::slots_read_proc_stat);
}

void cpu_usage_workers::slot_start_workers()
{
    m_timer->start(1000);
}

void cpu_usage_workers::slots_read_proc_stat()
{
    QFile file("/proc/stat");

    if(file.open(QIODevice::ReadOnly))
    {
        QVariantMap result;

        QByteArray proc_stat = file.readAll();

        QTextStream in(&proc_stat);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            const QList<QString> times = line.simplified().split(' ');
            const QList<QString> times_calc = line.simplified().split(' ').mid(1);

            if(times.at(0).contains("cpu"))
            {
                const int idleTime = times.at(4).toInt();
                int totalTime = 0;

                int prevIdleTime = m_prev_times.value(times.at(0)).first;
                int prevTotalTime = m_prev_times.value(times.at(0)).second;

                foreach (const QString &time, times_calc) {
                    totalTime += time.toInt();
                }

                const auto cpu_usage = (1 - (1.0*idleTime - prevIdleTime) / (totalTime - prevTotalTime)) * 100.0;

                QPair<int, int> time;
                time.first = idleTime;
                time.second = totalTime;

                m_prev_times.insert(times.at(0), time);

                QRegExp reg("cpu\\d+");

                // only cpu_xx
                if(reg.exactMatch(times.at(0)))
                    result.insert(times.at(0), QVariant::fromValue(cpu_usage)); // for sending
            }
        }

        file.close();

        if(result.size() > 0)
            emit signal_result_cpu_usage(result);
    }
}
