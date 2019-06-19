import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.3

Dialog {
    id: newJobDialog
    title: customizeTitle.checked ? windowTitleField.text : "Hello"
    standardButtons: StandardButton.Save | StandardButton.Cancel
    onAccepted: lastChosen.text = "Accepted " +
        (clickedButton === StandardButton.Ok ? "(OK)" : (clickedButton === StandardButton.Retry ? "(Retry)" : "(Ignore)"))
    onRejected: lastChosen.text = "Rejected " +
        (clickedButton == StandardButton.Close ? "(Close)" : (clickedButton == StandardButton.Abort ? "(Abort)" : "(Cancel)"))
    onReset: lastChosen.text = "Reset"

    Label {
        text: "Nuevo Trabajo!"
    }
}





/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
