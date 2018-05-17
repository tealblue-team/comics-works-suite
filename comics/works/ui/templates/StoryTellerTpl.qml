import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../atoms" as CWA
import "../molecules" as CWM
import "../organisms" as CWO

GridLayout {
    id: root
    property alias charactersListView: charactersListView
    property alias panelsGrid: panelsGrid
    width: 1024
    height: 768
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
                Layout.fillWidth: true
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
                        color: CWA.Colors.shades400
                    }
                    Row {
                        CWA.H5 {
                            text: "Story"
                            color: CWA.Colors.shades400
                        }
                        CWA.H5 {
                            text: "Teller"
                            color: CWA.Colors.shades300
                        }
                    }
                }
            }
            CWO.CharactersList {
                id: charactersListView
                Layout.fillWidth: true
                onAddCharacterFieldReturnPressed: {
                    uc.create_character(addCharacterField.text,workspaceName)
                    addCharacterField.clear()
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
            CWO.PanelsListView {
                id: panelsListView
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: panelsGrid.model
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
        id: deskFocus
        Layout.fillWidth: true
        Layout.fillHeight: true
        focus: true
        CWM.Desk {
            id: desk
            anchors.fill: parent
            GridView {
                id: panelsGrid
                anchors.fill: parent
                anchors.margins: 8
                cellWidth: panelsGrid.width / 3
                cellHeight: 264
                model: []
                delegate: CWO.PanelCard {
                    id: panelCard
                    name.text: modelData.eid
                    description.placeholderText: "<%1>".arg(qsTr("add description"))
                    description.text: modelData.description
                    onDescriptionConfirmed: uc.describe_panel(modelData.eid, description.text)
                    addCharacterButton.enabled: charactersListView.count > 0
                    availableCharactersSelector.model: charactersListView.model
                    availableCharactersSelector.onItemClicked: uc.add_character_to_panel(name, modelData.eid)
                    onAddDialogButtonClicked: uc.add_dialog_to_panel(dialogContent, characterName, modelData.eid)
                }
            }
        }
    }
}
