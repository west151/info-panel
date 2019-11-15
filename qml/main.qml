import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.VirtualKeyboard 2.3

ApplicationWindow {
    id: id_window
    objectName: "mainWindow"
    visible: true
    width: 700
    height: 500
    title: qsTr("Info panel")

    SwipeView {
        id: id_swipe_view
        currentIndex: id_tab_bar.currentIndex
        width: id_window.width
        height: id_window.height

        InfoPanel{
            id: id_info_panel
            objectName: "infoPanel"
            width: id_swipe_view.width
            height: id_swipe_view.height
        }

        DMesgViewerForm {
            id: id_dmesg_viewer
        }
    }

    footer: TabBar {
        id: id_tab_bar
        currentIndex: id_swipe_view.currentIndex

        TabButton {
            text: qsTr("Information System")
        }

        TabButton {
            text: qsTr("System log")
        }
    }
}
