import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 980
    height: 620
    title: qsTr("Obi Wan Kenobi")
    Material.theme: Material.Dark

    TableView {
        property var columnWidths: [0.03, 0.25, 0.05, 0.05, 0.07, 0.1, 0.09, 0.09, 0.17, 0.12]
        property var columnNames: ["Id", "Descripción", "Ancho", "Medida", "Cantidad", "Estado", "Pendientes", "Reservados", "Fecha de entrega", "Prioridad"]
        function parseMeasure(value) {
            return value ? "mm" : "cm"
        }

        function parseState(value) {
            switch(value) {
            case 0: return "En Progreso"
            case 1: return "Listo"
            case 2: return "En Progreso"
            case 3: return "Completado"
            case 4: return "Cancelado"
            }
            return value
        }

        function parsePriority(value) {
            switch(value) {
            case 0: return "Baja"
            case 1: return "Normal"
            case 2: return "Alta"
            }
            return value
        }

        function parseDate(value) {
            return new Date(value).toLocaleString(Qt.locale("es_AR"),"dd/MM/yyyy hh:mm")
            //return Date.fromLocaleString(locale, value, "dd/MM/yyyy hh:mm")
        }

        function parseRegister(column, value) {
            if (column === 3) {
                return parseMeasure(value)
            }

            if (column === 5) {
                return parseState(value)
            }

            if (column === 8) {
                return parseDate(value)
            }

            if (column === 9) {
                return parsePriority(value)
            }

            return value
        }

        anchors.rightMargin: 16
        anchors.leftMargin: 16
        anchors.bottomMargin: 16
        anchors.topMargin: 16
        topMargin: columnsHeader.implicitHeight
        Timer {
            id: resizeDelay
            interval: 10
            repeat: false
            onTriggered: if (jobs_model.rowCount() > 0)jobs.forceLayout()
        }
        id: jobs
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        model: jobs_model
        clip: true
        onWidthChanged: resizeDelay.start()
        columnWidthProvider: function (column) {
            return columnWidths[column]*jobs.width
        }

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
                model: jobs.columns
                Label {
                    width: jobs.columnWidthProvider(modelData)
                    text: jobs.columnNames[modelData]
                    font.bold: true
                    font.family: "Verdana"
                    horizontalAlignment: Text.AlignHCenter
                    color: '#dcf3ff'
                    font.pixelSize: 13
                    padding: 10
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        delegate: Rectangle {
            id: reg
            color: row % 2 === 0 ? '#2b3c46' : '#22313a'
            Text {
                text: jobs.parseRegister(column, display)

                anchors.fill: parent
                anchors.margins: 10
                color: '#9bbcd1'
                font.pixelSize: 14
                font.family: "Verdana"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: {
                    if (column === 0 || column === 2 || column === 4 || column === 6 || column === 7)
                        return Text.AlignRight
                    else
                        return Text.AlignLeft
                }
            }
        }
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
