import QtQuick 2.4
import QtQuick.Controls 2.13

Item {
    id: element
    width: 720
    height: 500
    property alias cpu_spin_box: cpu_spin_box
    property alias pid_text_edit: pid_text_edit
    property alias list_view_process_monitor: list_view_process_monitor

    ListView {
        id: list_view_process_monitor
        y: 59
        height: 433
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 59
    }

    TextField {
        id: pid_text_edit
        x: 42
        y: 8
        width: 92
        height: 40
        text: ""
        enabled: true
        layer.enabled: false
    }

    SpinBox {
        id: cpu_spin_box
        x: 192
        y: 8
        width: 130
        height: 40
        from: 1
        enabled: true
        editable: false
        to: 100
        value: 1
    }

    Label {
        id: label
        x: 8
        y: 20
        text: qsTr("PID:")
    }

    Label {
        id: label1
        x: 154
        y: 20
        text: qsTr("CPU:")
    }
}
