#include "bluetooth_discovery_workers.h"

#include <QMetaEnum>

#ifdef QT_DEBUG
#include <QDebug>
#endif

template<typename QEnum>
QString QtEnumToString (const QEnum value)
{
  return QString(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

bluetooth_discovery_workers::bluetooth_discovery_workers(QObject *parent) : QObject(parent),
    local_device(new QBluetoothLocalDevice(this))
{
    qRegisterMetaType<QBluetoothDeviceInfo>("QBluetoothDeviceInfo");

    discovery_agent = new QBluetoothDeviceDiscoveryAgent(this);

    connect(discovery_agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &bluetooth_discovery_workers::slot_add_device);

    connect(discovery_agent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &bluetooth_discovery_workers::slot_scan_finished);

}

void bluetooth_discovery_workers::slot_start_workers()
{
#ifdef QT_DEBUG
    qDebug() << tr("Bluetooth Local Device:") << local_device->address();
#endif

    discovery_agent->start();
}

void bluetooth_discovery_workers::slot_start_scan()
{

}

void bluetooth_discovery_workers::slot_scan_finished()
{
#ifdef QT_DEBUG
    qDebug() << tr("===================== scan finished =====================");
#endif

    discovery_agent->start();
}

void bluetooth_discovery_workers::slot_add_device(const QBluetoothDeviceInfo &info)
{
    QString label = QString("%1 %2 [%3]")
            .arg(info.address().toString())
            .arg(info.name())
            .arg(service_classes_descr(info.serviceClasses()).join(","));

#ifdef QT_DEBUG
    qDebug() << label;
#endif

}

QStringList bluetooth_discovery_workers::service_classes_descr(const QBluetoothDeviceInfo::ServiceClasses &service_info) const
{
    QStringList classes_descr;

    const auto all_service_classes = {
        QBluetoothDeviceInfo::NoService,
        QBluetoothDeviceInfo::PositioningService,
        QBluetoothDeviceInfo::NetworkingService,
        QBluetoothDeviceInfo::RenderingService,
        QBluetoothDeviceInfo::CapturingService,
        QBluetoothDeviceInfo::ObjectTransferService,
        QBluetoothDeviceInfo::AudioService,
        QBluetoothDeviceInfo::TelephonyService,
        QBluetoothDeviceInfo::InformationService,
        QBluetoothDeviceInfo::AllServices
    };

    for(const auto &item: all_service_classes)
        if(service_info.testFlag(item))
            classes_descr.append(service_class_descr(item));

    return classes_descr;
}

QString bluetooth_discovery_workers::service_class_descr(const QBluetoothDeviceInfo::ServiceClass &class_info) const
{
    QString service_info_descr;

    switch (class_info) {
    case QBluetoothDeviceInfo::NoService:
        service_info_descr.append(tr("NoService"));  // The device does not provide any services
        break;
    case QBluetoothDeviceInfo::PositioningService:
        service_info_descr.append(tr("PositioningService"));  // The device provides positioning services
        break;
    case QBluetoothDeviceInfo::NetworkingService:
        service_info_descr.append(tr("NetworkingService"));  // The device provides networking services
        break;
    case QBluetoothDeviceInfo::RenderingService:
        service_info_descr.append(tr("RenderingService"));  // The device provides rendering services
        break;
    case QBluetoothDeviceInfo::CapturingService:
        service_info_descr.append(tr("CapturingService"));  // The device provides capturing services
        break;
    case QBluetoothDeviceInfo::ObjectTransferService:
        service_info_descr.append(tr("ObjectTransferService"));  // The device provides object transfer services
        break;
    case QBluetoothDeviceInfo::AudioService:
        service_info_descr.append(tr("AudioService"));  // The device provides audio services
        break;
    case QBluetoothDeviceInfo::TelephonyService:
        service_info_descr.append(tr("TelephonyService"));  // The device provides telephony services
        break;
    case QBluetoothDeviceInfo::InformationService:
        service_info_descr.append(tr("InformationService"));  // The device provides information services
        break;
    case QBluetoothDeviceInfo::AllServices:
        service_info_descr.append(tr("AllServices"));  // The device provides services of all types
        break;
    default:
        service_info_descr.append(tr("unknown class service"));
        break;
    }

    return service_info_descr;
}
