#include "system_info_workers.h"
#include <QFont>
#include <QSysInfo>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QMetaEnum>

static const QMap<QString, QNetworkInterface::InterfaceType> interface_type_name
{
    {"Ethernet", QNetworkInterface::Ethernet},
    {"Wifi", QNetworkInterface::Wifi},
    {"Loopback", QNetworkInterface::Loopback},
    {"Unknown", QNetworkInterface::Unknown}
};

template<typename QEnum>
QString QtEnumToString (const QEnum value)
{
  return QString(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

system_info_workers::system_info_workers(QObject *parent) : QObject(parent)
{

}

void system_info_workers::slot_start_workers()
{
    system_info font_info;
    QFont font;

    font_info.set_parameter_name(tr("font family"));
    font_info.set_parameter_value(font.family());

    // font family
    emit signal_result_system_info(font_info);

    // cpu architecture
    emit signal_result_system_info(system_info(tr("cpu architecture"), QSysInfo::currentCpuArchitecture()));
    // build cpu architecture
    emit signal_result_system_info(system_info(tr("build cpu architecture"), QSysInfo::buildCpuArchitecture()));
    // build abi
    emit signal_result_system_info(system_info(tr("build abi"), QSysInfo::buildAbi()));

    // kernel type
    emit signal_result_system_info(system_info(tr("kernel type"), QSysInfo::kernelType()));
    // kernel version
    emit signal_result_system_info(system_info(tr("kernel version"), QSysInfo::kernelVersion()));
    // product version
    emit signal_result_system_info(system_info(tr("product version"), QSysInfo::productVersion()));

    // network info
    QString local_host_name =  QHostInfo::localHostName();
    emit signal_result_system_info(system_info(tr("localhost name"), local_host_name));

    QList<QNetworkInterface> all_interfaces = QNetworkInterface::allInterfaces();

    for(QNetworkInterface net_interface: all_interfaces){
        QList<QNetworkAddressEntry> all_entries = net_interface.addressEntries();
        for(QNetworkAddressEntry entry: all_entries){
            if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol){
                QString param_name;
                QString param_value;

                param_name.append(tr("IPv4: "));
                param_name.append(interface_type_name.key(net_interface.type(), QtEnumToString(net_interface.type())));
                param_name.append(tr(": "));
                param_name.append(net_interface.name());

                param_value.append(entry.ip().toString());
                param_value.append(tr(" / "));
                param_value.append(entry.netmask().toString());
                if(!net_interface.hardwareAddress().isEmpty())
                    param_value.append(tr(" [%1]").arg(net_interface.hardwareAddress()));

                emit signal_result_system_info(system_info(param_name, param_value));
            }
        }
    }
}
