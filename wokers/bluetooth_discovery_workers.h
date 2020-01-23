#ifndef BLUETOOTH_DISCOVERY_WORKERS_H
#define BLUETOOTH_DISCOVERY_WORKERS_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceInfo>

#include "../model/system_info.h"
#include "../model/bluetooth_device_info.h"

class bluetooth_discovery_workers : public QObject
{
    Q_OBJECT
public:
    explicit bluetooth_discovery_workers(QObject *parent = nullptr);

signals:
    void signal_result_system_info(const system_info &);
    void signal_bluetooth_device_info(const bluetooth_device_info &);
    void signal_scan_finished();
    void signal_power_state(const bool &);

public slots:
    void slot_start_workers();
    void slot_start_scan();
    void slot_stop_scan();
    void slot_power_ctrl(const bool &power_ctrl);

private slots:
    void slot_scan_finished();
    void slot_add_device(const QBluetoothDeviceInfo &);
    void slot_host_mode_state_changed(QBluetoothLocalDevice::HostMode mode);

private:
    QBluetoothLocalDevice *m_local_device {Q_NULLPTR};
    QBluetoothDeviceDiscoveryAgent *m_discovery_agent {Q_NULLPTR};

    QStringList service_classes_descr(const QBluetoothDeviceInfo::ServiceClasses &) const;
    QString service_class_descr(const QBluetoothDeviceInfo::ServiceClass &) const;
};

#endif // BLUETOOTH_DISCOVERY_WORKERS_H
