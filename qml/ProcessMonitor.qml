import QtQuick 2.4

ProcessMonitorForm {

    list_view_process_monitor {
        clip: true
        focus: true
        model: process_model
        delegate: id_view_delegate

        onCountChanged: {
            list_view_process_monitor.positionViewAtEnd()
        }
    }

    Component {
        id: id_view_delegate

        Item {
            id: id_main_item
            x: 5
            width: list_view_process_monitor.width
            height: id_row.height

            Rectangle {
                width: list_view_process_monitor.width
                height: id_main_item.height
                color: index % 2 == 0 ? "#00000000" : "#E4DDE8"
            }

            Row {
                id: id_row
                anchors.verticalCenter: parent.verticalCenter
                width: id_main_item.width
                height: id_user.height

                Text {
                    id: id_user
                    text: user
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 13
                }

                Text {
                    id: id_pid
                    text: pid
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 13
                }

                Text {
                    id: id_cpu
                    text: Number(cpu).toLocaleString(Qt.locale(), "f", 1)  + " %"
                    wrapMode: Text.WordWrap
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 13
                }
                Text {
                    id: id_mem
                    text: Number(mem).toLocaleString(Qt.locale(), "f", 1)  + " %"
                    wrapMode: Text.WordWrap
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 13
                }
                Text {
                    id: id_command
                    text: command
                    wrapMode: Text.WordWrap
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 13
                }
                spacing: 10
            }
        }
    }




//    list_device_view {
//        clip: true
//        focus: true
//        model: bluetooth_device_model
//        delegate: id_view_delegate

//        onCountChanged: {
//            list_device_view.positionViewAtEnd()
//        }
//    }

//    Component {
//        id: id_view_delegate

//        Item {
//            id: id_main_item
//            x: 5
//            width: list_device_view.width
//            height: id_name.height

//            Rectangle {
//                width: list_device_view.width
//                height: id_main_item.height
//                color: index % 2 == 0 ? "#00000000" : "#E4DDE8"
//            }

//            Row {
//                id: row
//                anchors.verticalCenter: parent.verticalCenter
//                width: id_main_item.width

//                Text {
//                    id: id_date_time
//                    text: Qt.formatDateTime(date_time, "hh:mm:ss" )
//                    anchors.verticalCenter: parent.verticalCenter
//                    font.pointSize: 10
//                }

//                Text {
//                    id: id_address
//                    text: address
//                    anchors.verticalCenter: parent.verticalCenter
//                    font.pointSize: 10
//                }

//                Text {
//                    id: id_name
//                    text: name
//                    wrapMode: Text.WordWrap
//                    anchors.verticalCenter: parent.verticalCenter
//                    font.pointSize: 10
//                }
//                spacing: 10
//            }
//        }
//    }
}
