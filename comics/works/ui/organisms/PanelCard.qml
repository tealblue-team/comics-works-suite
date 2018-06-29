import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import "../atoms" as CWA
import "../molecules" as CWM

FocusScope {
    id: root

    width: 256
    height: width + 1

    signal descriptionConfirmed(var event)
    signal nameConfirmed(var event)
    signal addDialogButtonClicked(string characterName, string dialogContent)

    property alias name: name
    property alias description: description
    property alias addCharacterButton: addCharacterButton
    property alias dialogField: dialogField
    property alias availableCharactersSelector: availableCharactersSelector
    property alias dialogsList: dialogsList
    property alias panelCharactersList: panelCharactersList
    property alias indexLabel: indexLabel

    Rectangle {
        width: root.width
        height: width
        radius: 4
        color: CWA.Colors.shades600
        y: 1
        opacity: .8
    }
    Rectangle {
        id: pageFace
        width: root.width
        height: width
        color: CWA.Colors.shades0
        radius: 4
    }
    TextField {
        id: name
        font.pixelSize: CWA.Typo.p2
        color: CWA.Colors.shades500
        padding: 4
        width: parent.width - 8
        height: implicitHeight
        placeholderText: "<add name>"
        Keys.onEscapePressed: focus = false
        Keys.onReturnPressed: nameConfirmed(event)
        wrapMode: TextArea.Wrap
        background: Item {}
    }
    TextArea {
        id: description
        font.pixelSize: CWA.Typo.p2
        color: CWA.Colors.shades500
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
            id: dialogsList
            model: [
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
                CWM.InlineTextPicButton {
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
            CWM.InlineIconButton {
                id: dialogCharacterButton
                size: "S"
                anchors.verticalCenter: dialogField.verticalCenter
                opacity: .6
                onClicked: panelCharactersSelector.visible = ! panelCharactersSelector.visible
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
                        id: chooseDialogCharacterButton
                        color: CWA.Colors.shades400
                        text: qsTr("add dialog...")
                        anchors.verticalCenter: parent.verticalCenter
                        visible: ! dialogField.displayText
                    }
                }
            }
        }
        Row {
            id: panelCharactersSelector
            x: 8
            spacing: 4
            visible: false
            Repeater {
                model: panelCharactersList.model
                delegate: CWM.InlineTextPicButton {
                    size: "S"
                    text: modelData
                    onClicked: {
                        if (dialogField.displayText) {
                            addDialogButtonClicked(modelData, dialogField.displayText)
                            panelCharactersSelector.visible = false
                        }
                    }
                }
            }
        }
    }
    CWM.InlineSelectionList {
        id: availableCharactersSelector
        anchors.right: parent.right
        anchors.bottom: panelCharactersRow.top
        anchors.margins: 8
        visible: false
        onItemClicked: visible = !visible
    }
    Row {
        id: panelCharactersRow
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 8
        spacing: 4
        Repeater {
            id: panelCharactersList
            model: ["first character","second character"]
            delegate: CWM.InlineTextPicButton {
                enabled: false
                text: modelData
                onClicked: if (dialogField.displayText) addDialogButtonClicked(modelData, dialogField.displayText)
            }
        }
        CWM.InlineIconButton {
            id: addCharacterButton
            onClicked: availableCharactersSelector.visible = ! availableCharactersSelector.visible
            opacity: .6
        }
    }
   CWA.P2 {
       id: indexLabel
       anchors.bottom: parent.bottom
       anchors.left: parent.left
       anchors.margins: 8
       text: "[idx]"
       verticalAlignment: Qt.AlignBottom
       color: CWA.Colors.shades300
   }
}

