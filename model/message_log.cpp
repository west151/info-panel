#include "message_log.h"

class message_log_data : public QSharedData {
public:
    message_log_data(): QSharedData()
    {
        m_log_id.clear();
        m_text_log.clear();
    }
    message_log_data(const message_log_data &other) : QSharedData(other)
    {
        m_log_id = other.m_log_id;
        m_text_log = other.m_text_log;
    }

    ~message_log_data() {}

    QString m_log_id;
    QString m_text_log;
};

message_log::message_log() : data(new message_log_data)
{
}

message_log::message_log(const QString &log_id, const QString &text_log)
{
    data->m_log_id = log_id;
    data->m_text_log = text_log;
}

message_log::message_log(const message_log &rhs) : data(rhs.data)
{
}

message_log &message_log::operator=(const message_log &rhs)
{
    if (this != &rhs) {
        data.operator=(rhs.data);
    }
    return *this;
}

message_log::~message_log()
{
}

void message_log::set_message_log_id(const QString &value)
{
    data->m_log_id = value;
}

QString message_log::message_log_id() const
{
    return data->m_log_id;
}

void message_log::set_message_log_text(const QString &value)
{
    data->m_text_log = value;
}

QString message_log::message_log_text() const
{
    return data->m_text_log;
}
