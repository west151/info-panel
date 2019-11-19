import QtQuick 2.4

InfoPanelForm {

    system_dt_text {
        text: user_interface.system_time
    }

    list_view_sysinfo {
        id: id_list_view_sysinfo
        clip: true
        focus: true
        model: system_info_model
        delegate: id_system_info_delegate

        onCountChanged: {
            id_list_view_sysinfo.positionViewAtEnd()
        }
    }

    Component {
        id: id_system_info_delegate

        Item {
            id: id_main_item
            x: 5
            width: id_list_view_sysinfo.width
            height: id_parameter_value.height

            Rectangle {
                width: id_list_view_sysinfo.width
                height: id_main_item.height
                color: index % 2 == 0 ? "#00000000" : "#E4DDE8"
            }

            Row {
                id: row
                anchors.verticalCenter: parent.verticalCenter
                width: id_main_item.width

                Text {
                    id: id_parameter_name
                    text: parameter_name + " : "
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 10
                }

                Text {
                    id: id_parameter_value
                    width: id_main_item.width - id_parameter_name.width
                    text: parameter_value
                    wrapMode: Text.WordWrap
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 10
                }
                spacing: 10
            }
        }
    }
}
