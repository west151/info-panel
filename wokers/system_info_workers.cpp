#include "system_info_workers.h"
#include <QFont>
#include <QSysInfo>
#include <QHostInfo>
#include <QNetworkInterface>

static const QMap<QString, QNetworkInterface::InterfaceType> interface_type_name
{
    {"Ethernet", QNetworkInterface::Ethernet},
    {"Wifi", QNetworkInterface::Wifi},
    {"Loopback", QNetworkInterface::Loopback}
};

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

//    QString local_mac_address;
//    QString local_netmask;
//    foreach (const QNetworkInterface& network_interface, QNetworkInterface::allInterfaces()) {
//        foreach (const QNetworkAddressEntry& entry, network_interface.addressEntries()) {
//            if (entry.ip().toString() == local_host_ip) {
//                local_mac_address = network_interface.hardwareAddress();
//                local_netmask = entry.netmask().toString();
//                break;
//            }
//        }
//    }


//    emit signal_result_system_info(system_info(tr("ip"), local_host_ip));
//    emit signal_result_system_info(system_info(tr("mac"), local_mac_address));
//    emit signal_result_system_info(system_info(tr("netmask"), local_netmask));


//    foreach (const QNetworkInterface &netInterface, QNetworkInterface::allInterfaces()) {
//        QNetworkInterface::InterfaceFlags flags = netInterface.flags();
//        if( (bool)(flags & QNetworkInterface::IsRunning) && !(bool)(flags & QNetworkInterface::IsLoopBack)){
//            foreach (const QNetworkAddressEntry &address, netInterface.addressEntries()) {
//                if(address.ip().protocol() == QAbstractSocket::IPv4Protocol)
//                    qDebug() << "->" << address.ip().toString();
//            }
//        }
//    }

    QList<QNetworkInterface> all_interfaces = QNetworkInterface::allInterfaces();

    for(QNetworkInterface eth: all_interfaces){
        QList<QNetworkAddressEntry> all_entries = eth.addressEntries();
        for(QNetworkAddressEntry entry: all_entries){
            if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol){
                qDebug() << "IPv4:" << interface_type_name.key(eth.type(), tr("unknown")) << ":" << eth.name() << ":" << entry.ip().toString() << "/" << entry.netmask().toString();
            }
        }
    }
}
