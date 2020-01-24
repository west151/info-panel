#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H

#include <QSharedData>
#include <QMetaType>

class process_info_data;

class process_info
{
public:
    process_info();
    process_info(const process_info &);
    process_info &operator=(const process_info &);
    ~process_info();

    void set_user(const QString &);
    QString user()const;

    void set_pid(const int &);
    int pid()const;

    void set_cpu_usage(const float &);
    float cpu_usage()const;

    void set_mem_usage(const float &);
    float mem_usage()const;

    void set_command(const QString &);
    QString command()const;

private:
    QSharedDataPointer<process_info_data> data;
};

Q_DECLARE_METATYPE(process_info)

#endif // PROCESS_INFO_H
