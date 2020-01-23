import QtQuick 2.4

CpuUsageForm {

    list_view_cpu_usage {
        id: id_list_view_cpu_usage
        clip: true
        focus: true
        model: cpu_usage_model
        delegate: id_cpu_usage_delegate
    }

    Component {
        id: id_cpu_usage_delegate

        Item {
            id: id_main_item
            x: 5
            width: id_list_view_cpu_usage.width
            height: id_row.height

            property double minimum: 0
            property double value: cpu_usage
            property double maximum: 100

            Row {
                id: id_row
                spacing: 10

                Text {
                    id: id_cpu_name
                    text: cpu_name
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }

                Rectangle {
                    id: id_progress_bar

                    height: id_row.height - 3
                    border.color: "black"
                    radius: 0.2 * height
                    width: id_main_item.width - id_cpu_name.width - 100
                    anchors.verticalCenter: parent.verticalCenter

                    Rectangle {
                        visible: value > minimum
                        x: 0.1 * id_progress_bar.height;  y: 0.1 * id_progress_bar.height
                        width: Math.max(height,
                                        Math.min((value - minimum) / (maximum - minimum) * (parent.width - 0.2 * id_progress_bar.height),
                                                 parent.width - 0.2 * id_progress_bar.height)) // clip
                        height: 0.8 * id_progress_bar.height
                        color: 'black'
                        radius: parent.radius
                    }
                }

                Text {
                    id: id_cpu_usage
                    text: cpu_usage + " %"
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }
}
