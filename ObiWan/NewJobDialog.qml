import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import Qt.labs.calendar 1.0
import QtQml 2.3

Dialog {
    id: newJobDialog
    width: 600
    height: 600
    modal: true
    standardButtons: StandardButton.Save | StandardButton.Cancel
    onAccepted: console.log("Al aceptar el Dialogo: " + calendar.selectedDate)

    RowLayout {
        id: name_row
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.left: parent.left
        anchors.leftMargin: 12
        Label {
            id: name_label
            text: "Nombre: "
        }

        TextField {
            id: name
            placeholderText: "Nombre del trabajo"
            Layout.fillWidth: true
        }
    }

    RowLayout {
        id: cut_row
        spacing: 2
        anchors.top: name_row.bottom
        anchors.topMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.left: parent.left
        anchors.leftMargin: 12
        Label {
            id: cut_quantity_label
            text: "Cortes: "
        }

        SpinBox {
            id: cut_quantity
            width: 140
            Layout.maximumWidth: 140
            value: 1
            padding: 0
            font.pointSize: 14
            editable: true
            spacing: 0
            rightPadding: 0
            bottomPadding: 0
            topPadding: 0
            leftPadding: 0
            to: 100000
            from: 1
        }

        Label {
            id: cut_size_label
            text: "Altura: "
        }

        SpinBox {
            id: cut_size_value
            width: 140
            Layout.maximumHeight: 140
            Layout.maximumWidth: 140
            font.pointSize: 14
            editable: true
            spacing: 0
            rightPadding: 0
            bottomPadding: 0
            topPadding: 0
            leftPadding: 0
            to: 10000
            from: 1
        }

        ComboBox {
            id: size_measure
            model: ["cm", "mm"]
        }
    }

    RowLayout {
        id: behavior_row
        anchors.top: cut_row.bottom
        anchors.topMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.left: parent.left
        anchors.leftMargin: 12
        Label {
            id: behavior_state_label
            text: "Estado Inicial: "
        }
        ComboBox {
            id: behavior_state
            width: 140
            model: ["Ingresado", "Listo"]
        }

        Label {
            id: behavior_priority_label
            text: "Prioridad: "
        }

        ComboBox {
            id: behavior_priority
            width: 140
            model: ["Alta", "Media", "Baja"]
        }

    }
    ColumnLayout {
        id: date_row
        anchors.top: behavior_row.bottom
        anchors.topMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.left: parent.left
        anchors.leftMargin: 12
        Label {
            id: date_priority_label
            text: "Fecha de entrega"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        ObiCalendar {
            id: calendar
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onSelectDate: console.log("Fecha en el popup" + date)
        }

    }
}
