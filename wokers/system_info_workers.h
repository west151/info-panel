#ifndef SYSTEM_INFO_WORKERS_H
#define SYSTEM_INFO_WORKERS_H

#include <QObject>

class system_info_workers : public QObject
{
    Q_OBJECT
public:
    explicit system_info_workers(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SYSTEM_INFO_WORKERS_H
