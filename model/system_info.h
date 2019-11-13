#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <QSharedData>
#include <QMetaType>

class system_info_data;

class system_info
{
public:
    system_info();
    system_info(const QString &name, const QString &value);
    system_info(const system_info &);
    system_info &operator=(const system_info &);
    ~system_info();

    void set_parameter_name(const QString &);
    QString parameter_name()const;

    void set_parameter_value(const QString &);
    QString parameter_value()const;

private:
    QSharedDataPointer<system_info_data> data;
};

Q_DECLARE_METATYPE(system_info)

#endif // SYSTEM_INFO_H
