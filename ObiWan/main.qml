import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Obi Wan Kenobi")
    Material.theme: Material.Dark

    Button {
        id: new_job
        text: qsTr("Nuevo Trabajo")
        font.weight: Font.Bold
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 16
        transformOrigin: Item.Center
        anchors.right: parent.right
        anchors.rightMargin: 16
        Material.accent: Material.Orange
        onClicked: new_job_dialog.open()

    }

    NewJobDialog {
        id: new_job_dialog
        anchors.centerIn: parent
        title: "Nuebo Trabajo"
        modal: true
        closePolicy: "CloseOnEscape"

    }

}
