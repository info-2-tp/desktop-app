import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.3
import QtQuick.Shapes 1.13

Dialog {
    id: cube_dialog
    property int cube_size
    property int current_cuts: 0
    property int current_cut_position: 0
    property var lines: []
    width: 600
    height: 600
    modal: true

    function ack() {
        cut_state.text = "Terminado"
        cut_size.text = ""
        mm.visible = false
        cube.children[cube_dialog.current_cuts-1].color = "#FFFFFF";
        arrow.y = cube.y - 10
    }

    function newCut(cutSize) {
        cube_dialog.current_cuts++;
        cube_dialog.current_cut_position+= cutSize;
        arrow.y = arrow.y + cutSize;
        cut_state.text = "Corte " + cube_dialog.current_cuts;
        cut_size.text = cutSize;
        mm.visible = true;
        if (cube_dialog.current_cuts > 1) cube.children[cube_dialog.current_cuts-2].color = "#FFFFFF";
        var line = Qt.createQmlObject('import QtQuick 2.0;
            Rectangle {
            id: cut_line_' + cube_dialog.current_cuts + ';
            width: 200;
            height: 1;
            x: 0;
            y: ' + cube_dialog.current_cut_position + ';
            color: "#AA0000";
           }
        ', cube, 'firstObject');
        lines.push(line);
    }

    Rectangle {
        id: cube
        x: 200
        y: 100
        width: 200
        height: cube_size
        color: "#d0b738"
    }

    Shape {
        id: arrow
        x: 400
        y: cube.y - 10
        width: 30
        height: 20
        ShapePath {
            fillColor: "#cccccc"
            strokeWidth: 2
            strokeColor: "black"
            startX: 5; startY: 0
            PathLine { x: 30; y: 0 }
            PathLine { x: 30; y: 20 }
            PathLine { x: 5; y: 20 }
            PathLine { x: 0; y: 10 }
            PathLine { x: 5; y: 0 }
        }
        Behavior on y {
            NumberAnimation {
                //This specifies how long the animation takes
                duration: 1000
                //This selects an easing curve to interpolate with, the default is Easing.Linear
                easing.type: Easing.InOutQuad
            }
        }
    }

    Text {
        id: element
        x: 8
        y: 8
        width: 95
        height: 28
        color: "#cccccc"
        text: qsTr("Cubo de ")
        fontSizeMode: Text.Fit
        lineHeight: 0.5
        wrapMode: Text.WrapAnywhere
        font.pixelSize: 24
    }

    Text {
        id: cube_size_label
        x: 102
        y: 8
        color: "#cccccc"
        text: cube_size
        font.pixelSize: 24
    }

    Text {
        id: element2
        x: 151
        y: 8
        color: "#cccccc"
        text: qsTr("mm")
        font.pixelSize: 24
    }

    Text {
        id: cut_state
        x: 337
        y: 8
        width: 151
        height: 28
        color: "#cccccc"
        text: qsTr("Preparando")
        wrapMode: Text.WrapAnywhere
        font.pixelSize: 24
        lineHeight: 0.5
        fontSizeMode: Text.Fit
    }

    Text {
        id: cut_size
        x: 494
        y: 8
        width: 31
        height: 28
        color: "#cccccc"
        wrapMode: Text.WrapAnywhere
        font.pixelSize: 24
        lineHeight: 0.5
        fontSizeMode: Text.Fit
    }

    Text {
        id: mm
        x: 531
        y: 8
        visible: false
        width: 31
        height: 28
        color: "#cccccc"
        text: qsTr("mm")
        verticalAlignment: Text.AlignBottom
        wrapMode: Text.WrapAnywhere
        font.pixelSize: 24
        lineHeight: 0.5
        fontSizeMode: Text.Fit
    }
}
