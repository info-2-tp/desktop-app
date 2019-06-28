import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.3


Calendar {
    Material.theme: Material.Dark
    minimumDate: new Date()
    style: CalendarStyle {
        navigationBar: Rectangle {
                color: "#2e414c"
                height: dateText.height * 2

                Rectangle {
                    color: Qt.rgba(1, 1, 1, 0.6)
                    height: 1
                    width: parent.width
                }

                Rectangle {
                    anchors.bottom: parent.bottom
                    height: 1
                    width: parent.width
                    color: "#ddd"
                }
                ToolButton {
                    id: previousMonth
                    width: parent.height
                    height: width
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    text: "<<"
                    onClicked: control.showPreviousMonth()
                }
                Label {
                    id: dateText
                    text: styleData.title
                    font.pixelSize: defaultFontPixelSize * 1.5
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    fontSizeMode: Text.Fit
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: previousMonth.right
                    anchors.leftMargin: 2
                    anchors.right: nextMonth.left
                    anchors.rightMargin: 2
                }
                ToolButton {
                    id: nextMonth
                    width: parent.height
                    height: width
                    text: qsTr(">>")
                    opacity: 0.8
                    font.weight: Font.bold
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    onClicked: control.showNextMonth()

                }


            }
        dayOfWeekDelegate: Rectangle {
                color: "#2e414c"
                implicitHeight: 36
                Label {
                    text: control.__locale.dayName(styleData.dayOfWeek, control.dayOfWeekFormat)
                    anchors.centerIn: parent
                }
            }
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















/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
