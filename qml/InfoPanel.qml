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

        Rectangle {
            id: main_rectangle
            x: 5
            width: list_view_sysinfo.width - 5
            height: id_text_info.height + 10
            color: alt_color(index % 2)

            Row {
                id: id_row
                anchors.verticalCenter: parent.verticalCenter

                Text {
                    id: id_text_info
                    width: main_rectangle.width - 5
                    text: parameter_name + " :  " + parameter_value
                    wrapMode: Text.WordWrap
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 15
                }
                //spacing: 50
            }

            function alt_color(i) {
                var colors = [ "#E4DDE8", "#00000000" ];
                return colors[i];
            }
        }
    }

    system_dt_text {
        text: info_panel_model.system_time
    }
}
