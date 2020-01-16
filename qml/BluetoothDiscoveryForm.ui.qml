import QtQuick 2.4
import QtQuick.Controls 2.13

Item {
    id: element
    width: 720
    height: 500
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
}

/*##^##
Designer {
    D{i:1;anchors_height:433;anchors_width:704;anchors_x:8;anchors_y:107}
}
##^##*/
