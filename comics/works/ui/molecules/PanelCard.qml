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

    signal descriptionConfirmed(var event)

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
        color: CWA.Colors.shades600
        y: 1
        opacity: .8
    }
    Rectangle {
        id: pageFace
        width: panel.width
        height: width
        color: CWA.Colors.shades0
        radius: 4
    }
    CWA.P2 {
        id: name
        x: 8
        y: 8
        text: "[panel name]"
        opacity: .5
    }
    TextArea {
        id: description
        font.pixelSize: CWA.Typo.p2
        color: CWA.Colors.shades600
        anchors.top: name.bottom
        padding: 4
        focus: true
        width: parent.width - 8
        height: implicitHeight
        placeholderText: "<add description>"
        Keys.onEscapePressed: focus = false
        Keys.onReturnPressed: descriptionConfirmed(event)
        wrapMode: TextArea.Wrap
    }
    Column {
        id: dialogs
        anchors.top: description.bottom
        width: parent.width
        spacing: 4
        Repeater {
            model: typeof(modelData) != "undefined" ? modelData.dialogs : [
                                                          {
                                                              "characterName":"first character",
                                                              "dialogContent_en_US":"I am an example of a fairly long dialog that might stretch more than one line"
                                                          },
                                                          {
                                                              "characterName":"second character",
                                                              "dialogContent_en_US":"I am a shorter dialog"
                                                          }
                                                      ]
            delegate: Row {
                x: 8
                spacing: 8
                width: dialogs.width - 8
                height: childrenRect.height
                CWA.CharacterBadge {
                    text: modelData.characterName.substring(0,3)
                    size: "S"
                }
                Text {
                    color: CWA.Colors.shades700
                    font.pixelSize: CWA.Typo.p2
                    width: parent.width - 48
                    wrapMode: Text.Wrap
                    height: implicitHeight
                    text: modelData.dialogContent_en_US
                }
            }
        }
        Row {
            x: 8
            spacing: 8
            width: dialogs.width - 8
            height: childrenRect.height
            CWA.AddDialogBadge {
                anchors.verticalCenter: dialogField.verticalCenter
                opacity: .6
            }
            TextField {
                id: dialogField
                width: parent.width - 40
                padding: 0
                font.pixelSize: CWA.Typo.p2
                background: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 32
                    color: "transparent"
                    border.color: "transparent"
                    CWA.P2 {
                        color: CWA.Colors.shades400
                        text: qsTr("add dialog...")
                        anchors.verticalCenter: parent.verticalCenter
                        visible: ! dialogField.displayText
                    }
                }
            }
        }
    }
    Rectangle {
        id: availableCharactersPane
        z: 10
        visible: false
        anchors.right: parent.right
        anchors.margins: 8
        radius: 4
        anchors.bottom: panelCharactersRow.top
        width: 80
        height: availableCharactersListView.count * 24 + 8
        color: CWA.Colors.shades200
        ListView {
            id: availableCharactersListView
            anchors.fill: parent
            anchors.margins: 4
            delegate: ItemDelegate {
                padding: 0
                text: modelData.name
                font.pixelSize: CWA.Typo.p2
                onClicked: {
                    uc.add_character_to_panel(modelData.name, panelCard.name.text)
                    parent.parent.visible = false
                }
                width: parent.width
                height: 24
            }
        }
    }
    Row {
        id: panelCharactersRow
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 8
        spacing: 4
        Repeater {
            id: panelCharacters
            model: typeof(modelData) != "undefined" ? modelData.characters : ["first character","second character"]
            delegate: CWA.CharacterBadge {
                text: modelData
                onClicked: if (dialogField.displayText) addDialogButtonClicked(modelData, dialogField.displayText)
            }
        }
        CWA.AddCharacterBadge {
            id: addCharacterBadge
            onClicked: availableCharactersPane.visible = ! availableCharactersPane.visible
            opacity: .6
        }
    }
}

