import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.3

Rectangle {
    Calendar {
        Material.theme: Material.Dark
        minimumDate: new Date()
        style: CalendarStyle {
            gridVisible: false
            dayDelegate: Rectangle {
                color: styleData.selected ? "#213139" : (styleData.visibleMonth && styleData.valid ? "#2a3c45" : "#394e5a")
                Label {
                    text: styleData.date.getDate()
                    anchors.centerIn: parent
                    color: styleData.valid ? "white" : "grey"
                }

                Rectangle {
                    width: parent.width
                    height: 1
                    color: "#394e5a"
                    anchors.bottom: parent.bottom
                }

                Rectangle {
                    width: 1
                    height: parent.height
                    color: "#394e5a"
                    anchors.right: parent.right
                }
            }
        }
    }
}






























/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
