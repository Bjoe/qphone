import QtQuick 2.0

Rectangle {
    width: 800
    height: 800
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

    Text {
        id: labelIncommingCall
        x: 40
        y: 18
        text: qsTr("Incoming Call")
        font.pixelSize: 12
    }

    Text {
        id: incomingCall
        x: 168
        y: 18
        width: 600
        height: 47
        text: qsTr("....")
        font.pixelSize: 12
    }


    Text {
        id: labelCallState
        x: 40
        y: 95
        text: qsTr("Call State")
        font.pixelSize: 12
    }

    Text {
        id: callState
        x: 168
        y: 95
        width: 600
        height: 74
        text: qsTr(".....")
        font.pixelSize: 12
    }


    Text {
        id: labelCallMediaState
        x: 40
        y: 210
        text: qsTr("Call MediaState")
        font.pixelSize: 12
    }

    Text {
        id: callMediastate
        x: 168
        y: 210
        width: 600
        height: 134
        text: qsTr("....")
        font.pixelSize: 12
    }

    Text {
        id: labelState
        x: 40
        y: 364
        text: qsTr("Status")
        font.pixelSize: 12
    }

    Text {
        id: state
        x: 168
        y: 364
        width: 600
        height: 300
        text: qsTr("....")
        font.pixelSize: 12
    }


    Button {
        id: login
        text: "Login"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 40

        onButtonClicked: qLogin()
    }

    Button {
        id: logout
        x: 168
        y: 698
        text: "Logout"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        anchors.left: login.right
        anchors.leftMargin: 28

        onButtonClicked: qLogout()
    }

    Button {
        id: busy
        x: 290
        y: 698
        text: "Besetzt"

        onButtonClicked: qBusy()
    }

    Button {
        id: cancel
        x: 414
        y: 698
        text: "Ablehnen"

        onButtonClicked: qCancel()
    }

    Button {
        id: ring
        x: 540
        y: 698
        text: "Klingeln"

        onButtonClicked: qRing()
    }

    Button {
        id: accept
        x: 668
        y: 698
        text: "Annehmen"

        onButtonClicked: qAccept()
    }
}
