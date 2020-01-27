import QtQuick 2.4
import QtQuick.Controls 2.13

Item {
    id: element
    width: 720
    height: 500
    property alias cbx_cpu: cbx_cpu
    property alias cpu_spin_box: cpu_spin_box
    property alias cbx_pid: cbx_pid
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
        x: 8
        y: 8
        width: 92
        height: 40
        text: ""
        layer.enabled: false
    }

    CheckBox {
        id: cbx_pid
        x: 111
        y: 8
        text: qsTr("PID")
    }

    SpinBox {
        id: cpu_spin_box
        x: 222
        y: 8
        enabled: false
        editable: false
        to: 100
        value: 2
    }

    CheckBox {
        id: cbx_cpu
        x: 379
        y: 8
        text: qsTr("CPU")
    }
}
