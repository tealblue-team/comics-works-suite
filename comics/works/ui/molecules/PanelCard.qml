import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "../atoms" as CWA
import "." as CWM

FocusScope {
    id: panel

    width: 256
    height: width

    property alias name: name
    property alias description: description
    property alias addCharacterButton: addCharacterButton
    property alias availableCharactersPane: availableCharactersPane

    signal addDialogButtonClicked(string characterName, string dialogContent)

    Rectangle {
        id: pageFace
        anchors.fill: parent
        color: CWA.Colors.shades0
    }
    DropShadow {
        source:pageFace
        anchors.fill: source
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8.0
        color: "#80000000"
    }
    Item {
        id: drawingSurface
        anchors.fill: parent
        anchors.margins: 32
    }
    Text {
        id: name
        anchors.horizontalCenter: parent.horizontalCenter
        text: "[panel name]"
        opacity: .5
    }
    TextField {
        id: description
        focus: true
        width: parent.width - 40
        placeholderText: "[panel description]"
        Keys.onEscapePressed: focus = false
    }
    CWM.AddCharacterButton {
        id: addCharacterButton
        anchors.right: parent.right
        anchors.top: parent.top
        enabled: charactersListView.count > 0
    }
    Column {
        id: characters
        anchors.top: addCharacterButton.bottom
        width: parent.width
        Repeater {
            model: modelData.characters
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
            model: modelData.dialogs
            Text {
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
            model: charactersListView.model
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
}

