import QtQuick 2.4

Item {
    id: element
    width: 720
    height: 500
    property alias list_view_cpu_usage: list_view_cpu_usage

    ListView {
        id: list_view_cpu_usage
        x: 305
        y: 170
        width: 400
        height: 200
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
