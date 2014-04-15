import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0
import Phone 1.0

ApplicationWindow {
    id: mainWindow
    title: qsTr("Phone")
    width: 600
    height: 300

    menuBar: MenuBar {
        Menu {
            title: qsTr("Datei")

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    statusBar: StatusBar {
        id: statusBar
        RowLayout {
            ProgressBar {
                id: statusBarProgress
            }
            Label {
                id: statusBarMessage
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        GroupBox {
            Layout.fillWidth: true

            RowLayout {
                anchors.fill: parent

                Label {
                    id: callToLabel
                    text: qsTr("Call to: ")
                }

                TextInput {
                    Layout.fillWidth: true

                    id: callTo
                    text: phone.callNumber
                    readOnly: false
                }
            }
        }

        GroupBox {
            Layout.fillWidth: true

            RowLayout {
                anchors.fill: parent

                Label {
                    id: incommingCallLabel
                    text: qsTr("Incoming Call")
                }

                Label {
                    Layout.fillWidth: true

                    id: incomingCall
                    text: phone.remoteInfo
                }
            }
        }

        GroupBox {
            Layout.fillWidth: true

            RowLayout {
                anchors.fill: parent

                Label {
                    id: callStateLabel
                    text: qsTr("Call State")
                }

                Label {
                    Layout.fillWidth: true

                    id: callState
                    text: phone.callState
                }
            }
        }

        GroupBox {
            Layout.fillWidth: true

            RowLayout {
                anchors.fill: parent

                Label {
                    id: callMediaStateLabel
                    text: qsTr("Call MediaState")
                }

                Label {
                    Layout.fillWidth: true

                    id: callMediastate
                    text: phone.mediaState
                }
            }
        }


        GroupBox {
            Layout.fillWidth: true

            RowLayout {
                anchors.fill: parent

                Label {
                    id: stateLabel
                    text: qsTr("Status")
                }

                Label {
                    Layout.fillWidth: true

                    id: state
                    text: phone.state
                }
            }
        }

        GroupBox {
            Layout.fillWidth: true

            RowLayout {
                anchors.fill: parent

                Button {
                    id: loginButton
                    text: "Login"

                    onClicked: phone.onLogin();
                }

                Button {
                    id: logoutButton
                    text: "Logout"

                    onClicked: phone.onLogout();
                }

                Button {
                    id: busyButton
                    text: "Besetzt"

                    onClicked: phone.onBusy();
                }

                Button {
                    id: cancelButton
                    text: "Ablehnen"

                    onClicked: phone.onCancel();
                }

                Button {
                    id: ringButton
                    text: "Klingeln"

                    onClicked: phone.onRing();
                }

                Button {
                    id: phoneButton
                    text: "Anrufen"

                    onClicked: {
                        if(phoneButton.state == "call") {
                            phoneButton.state = "hangup";
                            phone.onCall();
                        } else {
                            phoneButton.state = "call";
                            phone.onHangup();
                        }
                    }

                    states: [
                        State {
                            name: "call"
                            PropertyChanges {
                                target: phoneButton;
                                text: "Anrufen"
                            }
                        },
                        State {
                            name: "hangup"
                            PropertyChanges {
                                target: phoneButton
                                text: "Auflegen"
                            }
                        }
                    ]
                }
            }
        }
    }

    QPhone {
        id: phone
    }
}
