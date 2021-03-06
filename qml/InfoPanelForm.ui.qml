import QtQuick 2.4
import QtQuick.Controls 2.13

Item {
    id: element1
    width: 720
    height: 500
    property alias system_dt_text: system_dt_text
    property alias list_view_sysinfo: list_view_sysinfo
    property alias btn_shutdown_system: btn_shutdown_system
    property alias btn_reboot_system: btn_reboot_system


    Item {
        id: element2
        anchors.rightMargin: 8
        anchors.bottomMargin: 8
        anchors.leftMargin: 8
        anchors.topMargin: 68
        anchors.fill: parent

        ListView {
            id: list_view_sysinfo
            anchors.fill: parent
        }
    }

    Button {
        id: btn_reboot_system
        x: 8
        y: 12
        width: 150
        text: qsTr("Reboot")
        anchors.top: parent.top
        anchors.topMargin: 12
        anchors.left: parent.left
        anchors.leftMargin: 8
    }

    Button {
        id: btn_shutdown_system
        x: 562
        y: 12
        width: 150
        text: qsTr("Shutdown")
        anchors.top: parent.top
        anchors.topMargin: 12
        anchors.right: parent.right
        anchors.rightMargin: 8
    }

    Text {
        id: system_dt_text
        x: 323
        y: 21
        text: qsTr("00:00:00")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 21
        font.pixelSize: 19
    }
}

/*##^##
Designer {
    D{i:2;anchors_y:47}D{i:3;anchors_y:7}D{i:4;anchors_x:313;anchors_y:21}D{i:5;anchors_height:426;anchors_width:684;anchors_x:8;anchors_y:66}
}
##^##*/
