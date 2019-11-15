#ifndef DMESG_PROCESS_WOKERS_H
#define DMESG_PROCESS_WOKERS_H

#include <QObject>

class dmesg_process_wokers : public QObject
{
    Q_OBJECT
public:
    explicit dmesg_process_wokers(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DMESG_PROCESS_WOKERS_H
