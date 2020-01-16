#ifndef BLUETOOTH_DEVICE_INFO_H
#define BLUETOOTH_DEVICE_INFO_H

#include <QSharedData>
#include <QMetaType>
#include <QDateTime>

class bluetooth_device_info_data;

class bluetooth_device_info
{
public:
    bluetooth_device_info();
    bluetooth_device_info(const bluetooth_device_info &);
    bluetooth_device_info &operator=(const bluetooth_device_info &);
    ~bluetooth_device_info();

    void set_address(const QString &);
    QString address()const;

    void set_name(const QString &);
    QString name()const;

    void set_date_time(const QDateTime &);
    QDateTime date_time()const;

private:
    QSharedDataPointer<bluetooth_device_info_data> data;
};

Q_DECLARE_METATYPE(bluetooth_device_info)

#endif // BLUETOOTH_DEVICE_INFO_H
