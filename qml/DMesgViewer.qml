import QtQuick 2.4

DMesgViewerForm {
    id: id_dmesg_viewer

    btn_update_dmesg.onClicked: {
        message_log_model.slot_remove_data_from_model();
        user_interface.on_update_dmesg();
    }

    list_view_dmesg {
        clip: true
        focus: true
        model: message_log_model
        delegate: id_view_delegate

        onCountChanged: {
            list_view_dmesg.positionViewAtEnd()
        }
    }

    Component {
        id: id_view_delegate

        Item {
            id: id_main_item
            x: 5
            width: list_view_dmesg.width
            height: id_message_log_text.height

            Rectangle {
                width: list_view_dmesg.width
                height: id_main_item.height
                color: index % 2 == 0 ? "#00000000" : "#E4DDE8"
            }

            Row {
                id: row
                anchors.verticalCenter: parent.verticalCenter
                width: id_main_item.width

                Text {
                    id: id_message_log_id
                    text: message_log_id
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 10
                }

                Text {
                    id: id_message_log_text
                    width: id_main_item.width - id_message_log_id.width
                    text: message_log_text
                    wrapMode: Text.WordWrap
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 10
                }
                spacing: 10
            }
        }
    }
}
