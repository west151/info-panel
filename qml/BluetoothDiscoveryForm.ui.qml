import QtQuick 2.4
import QtQuick.Controls 2.13

Item {
    id: element
    width: 720
    height: 500
    property alias btn_scan_device: btn_scan_device
    property alias list_device_view: list_device_view

    ListView {
        id: list_device_view
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 59
    }

    Button {
        id: btn_scan_device
        x: 642
        width: 70
        height: 40
        text: qsTr("Scan")
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8
    }
}

/*##^##
Designer {
    D{i:1;anchors_height:433;anchors_width:704;anchors_x:8;anchors_y:107}
}
##^##*/
