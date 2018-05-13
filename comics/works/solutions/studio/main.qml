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
    width: 1024
    height: 768
    property string workspaceName: "workspace1"
    Component.onCompleted: uc.create_workspace(workspaceName)
    Connections {
        target: uc
        onWorkspaceCreated: {
            var jsonString = projectJson.readJsonFromFile("../../heavyLoad1.cw.json")
            projectJson.loadFromJsonDoc(jsonString)
        }
        onCharacterAddedToPanel: rep.model = value.panels
        onDialogAddedToPanel: rep.model = value.panels
        onCharacterCreated: charactersListView.model = value.characters
        onCharacterDeleted: {
            charactersListView.model = value.characters
            rep.model = value.panels
        }
        onPanelCreated: rep.model = value.panels
        onPanelDeleted: rep.model = value.panels
        onPanelDescribed: rep.model = value.panels
    }
    Connections {
        target: projectJson
        onSaved: {
            projectJson.writeJsonToFile(jsonDoc,"../../heavyLoad1.cw.json")
            snackbar.visible = true
            snackbar.text = qsTr("File saved")
            snackbarTimer.start()
        }
    }
    GridLayout {
        id: viewTpl
        anchors.fill: parent
        columnSpacing: 0
        Rectangle {
            color: CWA.Colors.shades600
            Layout.preferredWidth: 200
            Layout.fillHeight: true
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                anchors.topMargin: 8
                Row {
                    spacing: 8
                    CWA.CWLogoBw {
                        id: cwLogoBw
                        width: 40
                    }
                    Column {
                        anchors.verticalCenter: cwLogoBw.verticalCenter
                        spacing: -8
                        CWA.H5 {
                            text: "comics.works"
                            color: CWA.Colors.shades300
                        }
                        Row {
                            CWA.H5 {
                                text: "Studio"
                                color: CWA.Colors.shades400
                            }
                            CWA.H5 {
                                text: "Writer"
                                color: CWA.Colors.shades300
                            }
                        }
                    }
                }
                Row {
                    spacing: 8
                    CWA.Icon {
                        content: "characters"
                    }
                    CWA.H6 {
                        text: qsTr("Characters")
                        color: CWA.Colors.shades400
                    }
                }
                ListView {
                    id: charactersListView
                    Layout.fillWidth: true
                    Layout.preferredHeight: 96
                    model: []
                    spacing: 4
                    clip: true
                    delegate: Item {
                        width: parent.width
                        height: 20
                        CWA.P2 {
                            text: modelData.name
                            color: CWA.Colors.shades0
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        MouseArea {
                            anchors.right: parent.right
                            width: 24
                            height: 24
                            onClicked: uc.delete_character(modelData.name, workspaceName)
                            CWA.Icon {
                                content: "remove"
                                anchors.centerIn: parent
                            }
                        }
                    }
                    footer: TextField {
                        id: addCharacterField
                        color: CWA.Colors.shades0
                        background: Rectangle {
                            implicitWidth: 200
                            implicitHeight: 40
                            color: "transparent"
                            border.color: "transparent"
                            CWA.P2 {
                                color: CWA.Colors.shades0
                                opacity: .5
                                text: qsTr("add character...")
                                anchors.verticalCenter: parent.verticalCenter
                                visible: ! addCharacterField.displayText
                            }
                        }
                        Keys.onReturnPressed: {
                            uc.create_character(text,workspaceName)
                            clear()
                        }
                    }
                }
                Row {
                    spacing: 8
                    CWA.Icon {
                        content: "panel"
                    }
                    CWA.H6 {
                        text: qsTr("Panels")
                        color: CWA.Colors.shades400
                    }
                }
                ListView {
                    id: panelsListView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: rep.model
                    clip: true
                    delegate: Row {
                        spacing: 4
                        width: panelsListView.width
                        CWA.P2 {
                            text: modelData.eid
                            color: CWA.Colors.shades0
                            opacity: .8
                            width: 56
                        }
                        CWA.P2 {
                            text: modelData.description
                            color: CWA.Colors.shades0
                            elide: Text.ElideRight
                            width: panelsListView.width - 64
                        }
                    }
                    footer: Column {
                        width: panelsListView.width
                        Item {
                            width: parent.width
                            height: 20
                            CWA.P2 {
                                id: addPanelButton
                                text: qsTr("add panel")
                                color: CWA.Colors.shades0
                                opacity: .5
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: uc.create_panel("panel"+(rep.model.length+1), workspaceName)
                                }
                            }
                            CWA.Icon {
                                content: "add"
                                anchors.right: parent.right
                            }
                        }
                        Item {
                            width: parent.width
                            height: 20
                            CWA.P2 {
                                id: removePanelButton
                                text: qsTr("remove last panel")
                                color: CWA.Colors.shades0
                                opacity: .5
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: uc.delete_panel("panel"+(rep.model.length), workspaceName)
                                }
                                enabled: rep.model.length > 0
                            }
                            CWA.Icon {
                                content: "remove"
                                anchors.right: parent.right
                            }
                        }
                    }
                }
                Button {
                    text: "Save"
                    onClicked: projectJson.saveToJsonDoc()
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.margins: 16
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
                        description.placeholderText: "<%1>".arg(qsTr("add description"))
                        description.text: modelData.description
                        onDescriptionConfirmed: uc.describe_panel(modelData.eid, description.text)
                        addCharacterBadge.enabled: charactersListView.count > 0
                        availableCharactersListView.model: charactersListView.model
                        onAddDialogButtonClicked: {
                            uc.add_dialog_to_panel(dialogContent, characterName, modelData.eid)
                        }
                    }
                }
            }
            Label {
                id: snackbar
                anchors.top: parent.top
                anchors.margins: 16
                padding: 6
                anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle {color: CWA.Colors.shades600;radius:4}
                color: CWA.Colors.shades0
                font.pixelSize: CWA.Typo.p2
                width: 256
                height: 48
                horizontalAlignment: Label.AlignHCenter
                text: qsTr("hit <b>+</b> to add a panel,<br/><b>-</b> to remove the last created")
                Timer {
                    id: snackbarTimer
                    interval: 2500
                    running: true
                    onTriggered: parent.visible = false
                }
            }
        }
    }
}
