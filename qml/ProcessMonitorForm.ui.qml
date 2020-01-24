import QtQuick 2.4

Item {
    id: element
    width: 720
    height: 500
    property alias list_view_process_monitor: list_view_process_monitor

    ListView {
        id: list_view_process_monitor
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8
    }
}
