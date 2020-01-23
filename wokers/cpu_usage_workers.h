#ifndef CPU_USAGE_WORKERS_H
#define CPU_USAGE_WORKERS_H

#include <QObject>
#include <QMap>

class QTimer;

class cpu_usage_workers : public QObject
{
    Q_OBJECT
public:
    explicit cpu_usage_workers(QObject *parent = nullptr);

signals:
    void signal_result_cpu_usage(const QVariantMap &);

public slots:
    void slot_start_workers();

private:
    QTimer *m_timer;
    QMap<QString, QPair<int, int> > m_prev_times;

private slots:
    void slots_read_proc_stat();
};

#endif // CPU_USAGE_WORKERS_H
