import QtQuick 2.4

BluetoothDiscoveryForm {
    id: id_bluetooth_discovery_form

//    console.log("cbx_power_device.onCheckedChanged: " + cbx_power_device.checked)

    cbx_power_device.onCheckedChanged: {
        user_interface.on_power_ctrl(cbx_power_device.checked)
    }

//    cbx_power_device.checked: {
//        state: user_interface.power_state
//    }

    Connections {
        target: user_interface
        onSignal_power_state: {
            cbx_power_device.checked = user_interface.power_state
        }
    }

    btn_scan_device {
        onClicked: {
            user_interface.on_start_scan()
            btn_scan_device.state = "scan"
        }

        states: [
            State {
                name: "scan";
                PropertyChanges {
                    target: btn_scan_device;
                    enabled: false;
                    text: qsTr("Scanning");
                }
            },
            State {
                name: "finished";
                PropertyChanges {
                    target: btn_scan_device;
                    enabled: true;
                    text: qsTr("Scan")
                }
            }
        ]
    }

    Connections {
        target: user_interface
        onSignal_scan_state: {
            btn_scan_device.state = user_interface.scan_state
        }
    }

    list_device_view {
        clip: true
        focus: true
        model: bluetooth_device_model
        delegate: id_view_delegate

        onCountChanged: {
            list_device_view.positionViewAtEnd()
        }
    }

    Component {
        id: id_view_delegate

        Item {
            id: id_main_item
            x: 5
            width: list_device_view.width
            height: id_name.height

            Rectangle {
                width: list_device_view.width
                height: id_main_item.height
                color: index % 2 == 0 ? "#00000000" : "#E4DDE8"
            }

            Row {
                id: row
                anchors.verticalCenter: parent.verticalCenter
                width: id_main_item.width

                Text {
                    id: id_date_time
                    text: Qt.formatDateTime(date_time, "hh:mm:ss" )
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 10
                }

                Text {
                    id: id_address
                    text: address
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 10
                }

                Text {
                    id: id_name
                    text: name
                    wrapMode: Text.WordWrap
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 10
                }
                spacing: 10
            }
        }
    }
}
