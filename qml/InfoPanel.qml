import QtQuick 2.4

InfoPanelForm {

    list_view_sysinfo {
        clip: true
        focus: true
        model: system_info_model
        delegate: system_info_delegate

        onCountChanged: {
            list_view_sysinfo.positionViewAtEnd()
        }
    }

    Component {
        id: system_info_delegate
        Item {
            id: mainItem
            x: 5
            width: list_view_sysinfo.width
            height: idTextInfo.height

            Row {
                id: idRow
                anchors.verticalCenter: parent.verticalCenter

                Text {
                    id: idTextInfo
                    width: mainItem.width
                    text: parameter_name + " :  " + parameter_value
                    wrapMode: Text.WordWrap
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 13
                }
                spacing: 20
            }
        }
    }

    system_dt_text {
        text: info_panel_model.system_time
    }
}
