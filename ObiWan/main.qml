import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Window 2.2
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    property var r2d2
    id: mainWindow
    visible: true
    width: 980
    height: 620
    title: qsTr("Obi Wan Kenobi")
    Material.theme: Material.Dark

    function prepareCube(cubeSize) {
        if (mainWindow.r2d2) mainWindow.r2d2.destroy();
        mainWindow.r2d2 = Qt.createQmlObject('R2d2 {
        id: r2d2
        anchors.centerIn: parent
        title: "R2D2"
        modal: true
        closePolicy: "CloseOnEscape"
        }', mainWindow, 'lastObject');
        mainWindow.r2d2.open();
        mainWindow.r2d2.cube_size = cubeSize;
    }

    function showNewCut(cutSize) {
        mainWindow.r2d2.newCut(cutSize);
    }

    function ack() {
        mainWindow.r2d2.ack();
        setTimeout(destroyR2d2, 3000);
    }

    function destroyR2d2() {
        mainWindow.r2d2.destroy();
        mainWindow.r2d2 = null;
    }

    Connections {
        target: app
        onNewCubePrepare: {
            prepareCube(cubeSize)
        }
    }

    Connections {
        target: app
        onNewCut: {
            showNewCut(cutSize)
        }
    }

    Connections {
        target: app
        onNewAck: {
            ack()
        }
    }

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
        onClicked: {
            new_job_dialog.open()
            console.log("Boton precionado")
        }

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

    Timer {
        id: timer
        running: false
        repeat: false

        property var callback

        onTriggered: callback()
    }

    function setTimeout(callback, delay)
    {
        if (timer.running) {
            console.error("nested calls to setTimeout are not supported!");
            return;
        }
        timer.callback = callback;
        // note: an interval of 0 is directly triggered, so add a little padding
        timer.interval = delay + 1;
        timer.running = true;
    }
}
