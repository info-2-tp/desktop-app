import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 860
    height: 620
    title: qsTr("Obi Wan Kenobi")
    Material.theme: Material.Dark

    TableView {
        id: jobs
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        clip: true
        model: jobs_model
        delegate: Item {
            Text {
                text: display
                anchors.fill: parent
                anchors.margins: 10
                color: '#aaaaaa'
                font.pixelSize: 15
                verticalAlignment: Text.AlignVCenter
            }
        }
/*
        Rectangle { // mask the headers
            z: 3
            color: "#222222"
            y: jobs.contentY
            x: jobs.contentX
            width: jobs.leftMargin
            height: jobs.topMargin
        }
        Row {
            id: columnsHeader
            y: jobs.contentY
            z: 2
            Repeater {
                model: jobs.rows
                Label {
                    height: 35
                    text: jobs_model.
                    color: '#aaaaaa'
                    font.pixelSize: 15
                    padding: 10
                    verticalAlignment: Text.AlignVCenter

                    background: Rectangle { color: "#333333" }
                }
            }
        }
        Column {
            id: rowsHeader
            x: jobs.contentX
            z: 2
            Repeater {
                model: ["id", "Nombre", "Espesor"]
                Label {
                    width: 180
                    text: modelData
                    color: '#aaaaaa'
                    font.pixelSize: 15
                    padding: 10
                    verticalAlignment: Text.AlignVCenter

                    background: Rectangle { color: "#333333" }
                }
            }
        }*/
        ScrollIndicator.horizontal: ScrollIndicator { }
        ScrollIndicator.vertical: ScrollIndicator { }
    }

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
        onAccepted: {
            app.newJob(job_name, job_quantity, job_size, job_measure, job_state, job_priority, job_date)
        }
    }

}
