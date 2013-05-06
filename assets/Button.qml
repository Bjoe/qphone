import QtQuick 2.0

Rectangle {
    id: button
    width: 100
    height: 62
    radius: 10
    border.width: 2

    //determines the color of the button by using the conditional operator
    color: buttonMouseArea.pressed ? Qt.darker(buttonColor, 1.5) : buttonColor

    property color buttonColor: "blue"
    property color onHoverColor: "lightblue"
    property color borderColor: "grey"
    property alias text: label.text
    signal buttonClicked()

    Text {
        id: label
        text: "Button"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 12
    }

    MouseArea {
        id: buttonMouseArea
        anchors.fill: parent
        onClicked: buttonClicked()

        hoverEnabled: true
        onEntered: parent.border.color = onHoverColor
        onExited:  parent.border.color = borderColor
    }
}
