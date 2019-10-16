import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.VirtualKeyboard 2.3

ApplicationWindow {
    id: window
    objectName: "mainWindow"
    visible: true
    width: 700
    height: 500
    title: qsTr("Info panel")

    InfoPanel{
        id: idInfoPanel
        objectName: "infoPanel"
        width: window.width
        height: window.height
    }
}
