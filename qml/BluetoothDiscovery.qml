import QtQuick 2.4

BluetoothDiscoveryForm {
    id: id_bluetooth_discovery_form

    btn_scan_device {
        id: id_btn_scan_device
        //state: user_interface.scan_state
        onClicked: {
            user_interface.on_start_scan()
            id_btn_scan_device.state = "scan"
            console.log(" something happened " + user_interface.scan_state);
        }

        states: [
            State {
                name: "scan";
                PropertyChanges {
                    target: id_btn_scan_device;
                    enabled: false;
                }
            },
            State {
                name: "finished";
                PropertyChanges {
                    target: id_btn_scan_device;
                    enabled: true;
                }
            }
        ]
    }

    Connections {
        target: user_interface
        onSignal_scan_state: {
            console.log(" something happened " + user_interface.scan_state);
//            id_btn_scan_device.state = "scan"
            id_btn_scan_device.state = user_interface.scan_state
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
