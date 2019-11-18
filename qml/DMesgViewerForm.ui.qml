import QtQuick 2.4
import QtQuick.Controls 2.13

Item {
    id: element1
    width: 720
    height: 500
    property alias btn_update_dmesg: btn_update_dmesg
    property alias list_view_dmesg: list_view_dmesg

    Item {
        id: element2
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 59

        ListView {
            id: list_view_dmesg
            anchors.fill: parent
            leftMargin: 5
            rightMargin: 5
            bottomMargin: 5
            topMargin: 5
        }
    }

    Button {
        id: btn_update_dmesg
        x: 562
        width: 150
        height: 40
        text: qsTr("Update")
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8
    }
}

/*##^##
Designer {
    D{i:1;anchors_height:160;anchors_width:110;anchors_x:295;anchors_y:92}D{i:5;anchors_height:434;anchors_width:720;anchors_x:-568;anchors_y:8}
D{i:4;anchors_height:434;anchors_width:720;anchors_x:0;anchors_y:66}D{i:3;anchors_y:8}
}
##^##*/

