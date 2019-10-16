import QtQuick 2.4
import QtQuick.Controls 2.13

Item {
    id: element1
    width: 700
    height: 500
    property alias btn_shutdown_system: btn_shutdown_system
    property alias btn_reboot_system: btn_reboot_system


    Item {
        id: element
        height: 60
        anchors.top: parent.top
        anchors.topMargin: 445
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        Button {
            id: btn_reboot_system
            x: 8
            y: 47
            width: 130
            text: qsTr("Перезагрузить")
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
        }

        Button {
            id: btn_shutdown_system
            x: 562
            y: 7
            width: 130
            text: qsTr("Выключить")
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
        }
    }
}
