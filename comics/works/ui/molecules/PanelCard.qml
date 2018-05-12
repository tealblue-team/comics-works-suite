import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "../atoms" as CWA
import "." as CWM

FocusScope {
    id: panel

    width: 256
    height: width + 1

    property alias name: name
    property alias description: description
    property alias addCharacterBadge: addCharacterBadge
    property alias availableCharactersPane: availableCharactersPane
    property alias availableCharactersListView: availableCharactersListView

    signal addDialogButtonClicked(string characterName, string dialogContent)

    Rectangle {
        width: panel.width
        height: width
        radius: 4
        color: CWA.Colors.shades900
        y: 1
        opacity: .2
    }
    Rectangle {
        id: pageFace
        width: panel.width
        height: width
        color: CWA.Colors.shades0
        radius: 4
    }
    TextField {
        id: description
        focus: true
        width: parent.width - 40
        placeholderText: "[panel description]"
        Keys.onEscapePressed: focus = false
        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 40
            color: "transparent"
            border.color: "transparent"
            CWA.P2 {
                color: CWA.Colors.shades0
                opacity: .5
                text: qsTr(description.placeholderText)
                anchors.verticalCenter: parent.verticalCenter
                visible: ! description.displayText
            }
        }
    }
    Column {
        id: characters
        anchors.top: description.bottom
        width: parent.width
        Repeater {
            model: typeof(modelData) != "undefined" ? modelData.characters : ["character1","character2"]
            Row {
                width: characters.width
                TextField {
                    id: dialogField
                    placeholderText: modelData
                    width: parent.width - 40
                }
                CWM.AddDialogButton {
                    id: addDialogButton
                    onClicked: addDialogButtonClicked(modelData, dialogField.displayText)
                }
            }
        }
    }
    Column {
        id: dialogs
        anchors.top: characters.bottom
        width: parent.width
        Repeater {
            model: typeof(modelData) != "undefined" ? modelData.dialogs : [
                                                          {
                                                              "characterName":"character1",
                                                              "dialogContent_en_US":"dialog1"
                                                          },
                                                          {
                                                              "characterName":"character2",
                                                              "dialogContent_en_US":"dialog2"
                                                          }
                                                      ]
            CWA.P1 {
                width: dialogs.width
                wrapMode: Text.Wrap
                text: "<b>%1:</b> %2".arg(modelData.characterName).arg(modelData.dialogContent_en_US)
            }
        }
    }
    Pane {
        id: availableCharactersPane
        z: 10
        visible: false
        anchors.right: parent.right
        width: 80
        height: availableCharactersListView.count * 24 + padding * 2
        ListView {
            id: availableCharactersListView
            anchors.fill: parent
            delegate: ItemDelegate {
                text: modelData.name
                onClicked: {
                    uc.add_character_to_panel(modelData.name, panelCard.name.text)
                    parent.parent.visible = false
                }
                width: parent.width
            }
        }
    }
    Row {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 8
        spacing: 4
        Repeater {
            id: panelCharacters
            model: typeof(modelData) != "undefined" ? modelData.characters : ["character1","character2"]
            delegate: CWA.CharacterBadge {
                text: modelData
            }
        }
        CWA.AddCharacterBadge {
            id: addCharacterBadge
        }
    }
    CWA.P2 {
        id: name
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 8
        text: "[panel name]"
        opacity: .5
    }
}

