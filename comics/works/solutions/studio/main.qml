import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import comics.works.ui.atoms 1.0 as CWA
import comics.works.ui.molecules 1.0 as CWM

Window {
    id: mainWindow
    title: "comics.works"
    visible: true
    width: 256 * 3 + 48 + 200
    height: 600
    property string workspaceName: "workspace1"
    Component.onCompleted: uc.create_workspace(workspaceName)
    Connections {
        target: uc
        onWorkspaceCreated: projectJson.loadFrom("{"
                                                 +"\"characters\":[{\"name\":\"Ayran\"},{\"name\":\"Birun\"},{\"name\":\"Dilgun\"},{\"name\":\"Barsun\"}],"
                                                 +"\"panels\":["
                                                     +"{\"characters\":[\"Ayran\",\"Birun\"],\"description\":\"first scene\",\"dialogs\":[{\"characterName\":\"Ayran\",\"dialogContent_en_US\":\"Hello\"},{\"characterName\":\"Birun\",\"dialogContent_en_US\":\"Hi\"}],\"eid\":\"panel1\"},"
                                                     +"{\"characters\":[\"Barsun\",\"Dilgun\"],\"description\":\"second scene\",\"dialogs\":[{\"characterName\":\"Dilgun\",\"dialogContent_en_US\":\"Hey\"},{\"characterName\":\"Barsun\",\"dialogContent_en_US\":\"Hey there\"}],\"eid\":\"panel2\"}"
                                                 +"]"
                                             +"}")
        onCharacterAddedToPanel: rep.model = value.panels
        onDialogAddedToPanel: rep.model = value.panels
        onCharacterCreated: charactersListView.model = value.characters
        onPanelCreated: rep.model = value.panels
        onPanelDeleted: rep.model = value.panels
        onPanelDescribed: rep.model = value.panels
        onUsecaseCompleted: print(JSON.stringify(value.panels), JSON.stringify(value.characters))
    }
    GridLayout {
        id: viewTpl
        anchors.fill: parent
        columnSpacing: 0
        Rectangle {
            color: "#333"
            Layout.preferredWidth: 200
            Layout.fillHeight: true
            ColumnLayout {
                anchors.fill: parent
                TextField {
                    placeholderText: "add character"
                    Keys.onReturnPressed: {
                        uc.create_character(text,workspaceName)
                        clear()
                    }
                }
                ListView {
                    id: charactersListView
                    Layout.fillWidth: true
                    Layout.preferredHeight: 128
                    Layout.margins: 16
                    model: []
                    delegate: Text {
                        text: modelData.name
                        color: "#fff"
                    }
                }
                ListView {
                    id: panelsListView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.margins: 16
                    model: rep.model
                    delegate: Column {
                        Text {
                            text: modelData.eid
                            color: "white"
                            opacity: .8
                        }
                        Text {
                            x: 16
                            text: modelData.description
                            color: "white"
                        }
                    }
                }
                CWA.CWLogo {
                    anchors.bottom: parent.bottom
                }
            }
        }
        FocusScope {
            id: tableFocus
            Layout.fillWidth: true
            Layout.fillHeight: true
            focus: true
            Keys.onPressed: {
                if (event.key === Qt.Key_Plus) {
                    event.accepted = true
                    uc.create_panel("panel"+(rep.model.length+1), workspaceName)
                }
                if (event.key === Qt.Key_Minus) {
                    event.accepted = true
                    uc.delete_panel("panel"+(rep.model.length), workspaceName)
                }
            }
            CWM.Table {
                anchors.fill: parent
                GridView {
                    id: rep
                    anchors.fill: parent
                    anchors.margins: 8
                    cellWidth: rep.width / 3
                    cellHeight: 264
                    model: []
                    delegate: CWM.PanelCard {
                        id: panelCard
                        name.text: modelData.eid
                        description.placeholderText: modelData.description || "<add description>"
                        Keys.onReturnPressed: uc.describe_panel(modelData.eid, description.displayText)
                        addCharacterButton.onClicked: availableCharactersPane.visible = true
                        onAddDialogButtonClicked: {
                            uc.add_dialog_to_panel(dialogContent, characterName, modelData.eid)
                        }
                    }
                }
            }
            Button {
                id: addPanelButton
                onClicked: uc.create_panel("panel"+(rep.model.length+1), workspaceName)
                anchors.margins: 8
                anchors.top: parent.top
                anchors.right: parent.right
                text: "+"
                width: 40
                height: width
            }
            Button {
                id: removePanelButton
                onClicked: uc.delete_panel("panel"+(rep.model.length), workspaceName)
                anchors.margins: 8
                anchors.top: addPanelButton.bottom
                anchors.right: parent.right
                text: "-"
                width: 40
                height: width
                enabled: rep.model.length > 0
            }
        }
    }
    Label {
        anchors.top: parent.top
        anchors.margins: 16
        padding: 8
        anchors.horizontalCenter: parent.horizontalCenter
        background: Rectangle {color: "#333";radius:4}
        color: "white"
        width: 256
        height: 48
        horizontalAlignment: Label.AlignHCenter
        text: qsTr("hit <b>+</b> to add a panel,<br/><b>-</b> to remove the last created")
        Timer {
            interval: 2500
            running: true
            onTriggered: parent.visible = false
        }
    }
}
