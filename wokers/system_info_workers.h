#ifndef SYSTEM_INFO_WORKERS_H
#define SYSTEM_INFO_WORKERS_H

#include <QObject>

#include "../model/system_info.h"

class system_info_workers : public QObject
{
    Q_OBJECT
public:
    explicit system_info_workers(QObject *parent = nullptr);

signals:    
    void signal_result_system_info(const system_info &);

public slots:
    void slot_start_workers();

private:
};

#endif // SYSTEM_INFO_WORKERS_H
