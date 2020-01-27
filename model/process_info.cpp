#include "process_info.h"

class process_info_data : public QSharedData {
public:
    process_info_data(): QSharedData()
    {
        m_time_update = QTime::currentTime();
        m_user.clear();
        m_pid = 0;
        m_cpu_usage = 0.0;
        m_mem_usage = 0.0;
        m_command.clear();
    }
    process_info_data(const process_info_data &other) : QSharedData(other)
    {
        m_time_update = other.m_time_update;
        m_user = other.m_user;
        m_pid = other.m_pid;
        m_cpu_usage = other.m_cpu_usage;
        m_mem_usage = other.m_mem_usage;
        m_command = other.m_command;
    }

    ~process_info_data() {}

    QTime m_time_update;
    QString m_user;
    int m_pid;
    float m_cpu_usage;
    float m_mem_usage;
    QString m_command;
};

process_info::process_info() : data(new process_info_data)
{
}

process_info::process_info(const process_info &rhs) : data(rhs.data)
{
}

process_info &process_info::operator=(const process_info &rhs)
{
    if (this != &rhs) {
        data.operator=(rhs.data);
    }
    return *this;
}

process_info::~process_info()
{
}

QTime process_info::time_update() const
{
    return data->m_time_update;
}

void process_info::set_user(const QString &value)
{
    data->m_user = value;
}

QString process_info::user() const
{
    return data->m_user;
}

void process_info::set_pid(const int &value)
{
    data->m_pid = value;
}

int process_info::pid() const
{
    return data->m_pid;
}

void process_info::set_cpu_usage(const float &value)
{
    data->m_cpu_usage = value;
}

float process_info::cpu_usage() const
{
    return data->m_cpu_usage;
}

void process_info::set_mem_usage(const float &value)
{
    data->m_mem_usage = value;
}

float process_info::mem_usage() const
{
    return data->m_mem_usage;
}

void process_info::set_command(const QString &value)
{
    data->m_command = value;
}

QString process_info::command() const
{
    return data->m_command;
}
