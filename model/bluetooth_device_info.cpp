#include "bluetooth_device_info.h"

class bluetooth_device_info_data : public QSharedData {
public:
    bluetooth_device_info_data(): QSharedData()
    {
        m_address.clear();
        m_name.clear();
    }
    bluetooth_device_info_data(const bluetooth_device_info_data &other) : QSharedData(other)
    {
        m_address = other.m_address;
        m_name = other.m_name;
    }

    ~bluetooth_device_info_data() {}

    QString m_address;
    QString m_name;
};

bluetooth_device_info::bluetooth_device_info() : data(new bluetooth_device_info_data)
{
}

bluetooth_device_info::bluetooth_device_info(const bluetooth_device_info &rhs) : data(rhs.data)
{
}

bluetooth_device_info &bluetooth_device_info::operator=(const bluetooth_device_info &rhs)
{
    if (this != &rhs) {
        data.operator=(rhs.data);
    }
    return *this;
}

bluetooth_device_info::~bluetooth_device_info()
{
}

void bluetooth_device_info::set_address(const QString &value)
{
    data->m_address = value;
}

QString bluetooth_device_info::address() const
{
    return data->m_address;
}

void bluetooth_device_info::set_name(const QString &value)
{
    data->m_name = value;
}

QString bluetooth_device_info::name() const
{
    return data->m_name;
}
