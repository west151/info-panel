import QtQuick 2.4

ProcessMonitorForm {


    pid_text_edit {
        inputMethodHints: Qt.ImhDigitsOnly
        placeholderText: qsTr("Enter pid")
        onTextChanged: {
            console.log("onTextChanged: " + pid_text_edit.text)
            console.log("onTextChanged: " + pid_text_edit.text.length)
            user_interface.on_current_pid(pid_text_edit.text)
        }
    }

    cpu_spin_box {
        onValueChanged: {
            console.log("onToChanged: " + cpu_spin_box.value)
            user_interface.on_min_cpu_usage(cpu_spin_box.value)
        }
    }

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
                height: time_update.height

                Text {
                    id: id_time_update
                    text: Qt.formatTime(time_update, "mm:ss.zzz")
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 13
                }

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
}
