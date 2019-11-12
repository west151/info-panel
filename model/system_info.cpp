#include "system_info.h"

class system_info_data : public QSharedData {
public:
    system_info_data(): QSharedData()
    {
        m_parameter.clear();
        m_value.clear();
    }
    system_info_data(const system_info_data &other) : QSharedData(other)
    {
        m_parameter = other.m_parameter;
        m_value = other.m_value;
    }

    ~system_info_data() {}

    QString m_parameter;
    QString m_value;
};

system_info::system_info() : data(new system_info_data)
{
}

system_info::system_info(const system_info &rhs) : data(rhs.data)
{
}

system_info &system_info::operator=(const system_info &rhs)
{
    if (this != &rhs) {
        data.operator=(rhs.data);
    }
    return *this;
}

system_info::~system_info()
{
}

void system_info::set_parameter_name(const QString &value)
{
    data->m_parameter = value;
}

QString system_info::parameter_name() const
{
    return data->m_parameter;
}

void system_info::set_parameter_value(const QString &value)
{
    data->m_value = value;
}

QString system_info::parameter_value() const
{
    return data->m_value;
}
