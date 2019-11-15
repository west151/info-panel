#ifndef MESSAGE_LOG_H
#define MESSAGE_LOG_H

#include <QSharedData>
#include <QMetaType>

class message_log_data;

class message_log
{
public:
    message_log();
    message_log(const QString &log_id, const QString &text_log);
    message_log(const message_log &);
    message_log &operator=(const message_log &);
    ~message_log();

    void set_message_log_id(const QString &);
    QString message_log_id()const;

    void set_message_log_text(const QString &);
    QString message_log_text()const;    

private:
    QSharedDataPointer<message_log_data> data;
};

Q_DECLARE_METATYPE(message_log)

#endif // MESSAGE_LOG_H
