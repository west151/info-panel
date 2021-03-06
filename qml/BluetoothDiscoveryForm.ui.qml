import QtQuick 2.4
import QtQuick.Controls 2.13

Item {
    id: element
    width: 720
    height: 500
    property alias cbx_power_device: cbx_power_device
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
        x: 623
        width: 89
        height: 40
        text: qsTr("Scan")
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8
    }

    CheckBox {
        id: cbx_power_device
        x: 8
        y: 8
        text: qsTr("Bluetooth Powered On")
    }
}

/*##^##
Designer {
    D{i:1;anchors_height:433;anchors_width:704;anchors_x:8;anchors_y:107}
}
##^##*/
