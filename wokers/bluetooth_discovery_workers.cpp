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

bluetooth_discovery_workers::bluetooth_discovery_workers(QObject *parent) : QObject(parent)

{
    qRegisterMetaType<QBluetoothDeviceInfo>("QBluetoothDeviceInfo");
}

void bluetooth_discovery_workers::slot_start_workers()
{
    m_local_device = new QBluetoothLocalDevice(this);

#ifdef QT_DEBUG
    qDebug() << tr("Bluetooth Local Device:") << m_local_device->address();
#endif    

    m_discovery_agent = new QBluetoothDeviceDiscoveryAgent(this);
    // discovery_agent->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);

    connect(m_discovery_agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &bluetooth_discovery_workers::slot_add_device);

    connect(m_discovery_agent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &bluetooth_discovery_workers::slot_scan_finished);

    connect(m_local_device, &QBluetoothLocalDevice::hostModeStateChanged,
            this, &bluetooth_discovery_workers::slot_host_mode_state_changed);

    slot_host_mode_state_changed(m_local_device->hostMode());
}

void bluetooth_discovery_workers::slot_start_scan()
{
    m_discovery_agent->start();
}

void bluetooth_discovery_workers::slot_stop_scan()
{
    if(m_discovery_agent->isActive())
        m_discovery_agent->stop();
}

void bluetooth_discovery_workers::slot_power_ctrl(const bool &power_ctrl)
{
    if (power_ctrl)
        m_local_device->powerOn();
    else
        m_local_device->setHostMode(QBluetoothLocalDevice::HostPoweredOff);

#ifdef QT_DEBUG
    qDebug() << tr("receive power_ctrl:") << power_ctrl;
#endif
}

void bluetooth_discovery_workers::slot_scan_finished()
{
    emit signal_scan_finished();

#ifdef QT_DEBUG
    qDebug() << tr("scan finished");
#endif
}

void bluetooth_discovery_workers::slot_add_device(const QBluetoothDeviceInfo &info)
{
    bluetooth_device_info data;
    data.set_date_time(QDateTime::currentDateTimeUtc());
    data.set_address(info.address().toString());
    data.set_name(info.name());

    emit signal_bluetooth_device_info(data);

#ifdef QT_DEBUG
    qDebug() << tr("Bluetooth Device Info:");
    qDebug() << data.address();
    qDebug() << data.name();
    qDebug() << tr("**********************");
#endif
}

void bluetooth_discovery_workers::slot_host_mode_state_changed(QBluetoothLocalDevice::HostMode mode)
{
#ifdef QT_DEBUG
    qDebug() << tr("host mode state changed:") << QtEnumToString(mode);
#endif

    if (mode != QBluetoothLocalDevice::HostPoweredOff)
        emit signal_power_state(true);
    else
        emit signal_power_state(false);
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
