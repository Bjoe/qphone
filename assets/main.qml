import QtQuick 2.0

Item {
    width: 700
    height: 400
    visible: true
    id: rootObject

    signal qLogin()
    signal qLogout()
    signal qBusy()
    signal qCancel()
    signal qRing()
    signal qAccept()

    property alias qState: state.text
    property alias qCallMediaState: callMediastate.text
    property alias qCallState: callState.text
    property alias qIncommingCall: incomingCall.text
    property alias qAcceptText: accept.text
    property alias qCallNumber: callTo.text

    Rectangle {
        anchors.top: parent.top
        height: 50
        width: callToLabel.width + callTo.width + 15
        id: column1

        color: "lightgrey"

        Text {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 5
            id: callToLabel
            text: qsTr("Call to: ")
            font.pixelSize: 18
        }

        TextInput {
            anchors.top: parent.top
            anchors.left: callToLabel.right
            anchors.margins: 5
            width: 100
            id: callTo
            text: qsTr(".")
            font.pixelSize: 18
        }
    }

    Rectangle {
        anchors.top: column1.bottom
        height: 50

        id: column2

        Text {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 5
            id: incommingCallLabel
            text: qsTr("Incoming Call")
            font.pixelSize: 18
        }

        Text {
            anchors.top: parent.top
            anchors.left: incommingCallLabel.right
            anchors.margins: 5
            id: incomingCall
            text: qsTr("....")
            font.pixelSize: 18
        }
    }

    Rectangle {
        anchors.top: column2.bottom
        height: 50

        id: column3

        Text {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 5
            id: callStateLabel
            text: qsTr("Call State")
            font.pixelSize: 18
        }

        Text {
            anchors.top: parent.top
            anchors.left: callStateLabel.right
            anchors.margins: 5
            id: callState
            text: qsTr(".....")
            font.pixelSize: 18
        }

    }

    Rectangle {
        anchors.top: column3.bottom
        height: 50

        id: column4

        Text {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 5
            id: callMediaStateLabel
            text: qsTr("Call MediaState")
            font.pixelSize: 18
        }

        Text {
            anchors.top: parent.top
            anchors.left: callMediaStateLabel.right
            anchors.margins: 5
            id: callMediastate
            text: qsTr("....")
            font.pixelSize: 18
        }

    }


    Rectangle {
        anchors.top: column4.bottom
        height: 100

        id: column5

        Text {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 5
            id: stateLabel
            text: qsTr("Status")
            font.pixelSize: 18
        }

        Text {
            anchors.top: parent.top
            anchors.left: stateLabel.right
            anchors.margins: 5
            id: state
            text: qsTr("....")
            font.pixelSize: 18
        }

    }

    Rectangle {
        anchors.top: column5.bottom
        height: 50

        Button {
            anchors.top: parent.top
            anchors.left: parent.left

            id: login
            text: "Login"

            onButtonClicked: qLogin()
        }

        Button {
            anchors.top: parent.top
            anchors.left: login.right
            id: logout
            text: "Logout"

            onButtonClicked: qLogout()
        }

        Button {
            anchors.top: parent.top
            anchors.left: logout.right
            id: busy
            text: "Besetzt"

            onButtonClicked: qBusy()
        }

        Button {
            anchors.top: parent.top
            anchors.left: busy.right

            id: cancel
            text: "Ablehnen"

            onButtonClicked: qCancel()
        }

        Button {
            anchors.top: parent.top
            anchors.left: cancel.right

            id: ring
            text: "Klingeln"

            onButtonClicked: qRing()
        }

        Button {
            anchors.top: parent.top
            anchors.left: ring.right

            id: accept
            text: "Anrufen"

            onButtonClicked: qAccept()
        }
    }

}
