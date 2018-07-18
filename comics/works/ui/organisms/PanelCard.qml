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
    focus: true

    signal descriptionConfirmed(var event)
    signal nameConfirmed(var event)
    signal descriptionTabPressed(var event)
    signal descriptionBacktabPressed(var event)
    signal addDialogButtonClicked(string characterName, string dialogContent)

    property alias name: name
    property alias description: description
    property alias addCharacterButton: addCharacterButton
    property alias dialogField: dialogField
    property alias availableCharactersSelector: availableCharactersSelector
    property alias dialogsList: dialogsList
    property alias panelCharactersList: panelCharactersList
    property alias indexLabel: indexLabel
    KeyNavigation.tab: name

    Rectangle {
        width: root.width
        height: width
        radius: 4
        color: CWA.Colors.shades400
        y: 1
    }
    Rectangle {
        id: pageFace
        width: root.width
        height: width
        color: root.activeFocus ? CWA.Colors.shades0 : CWA.Colors.shades100
        radius: 4
    }
    TextField {
        id: name
//        focus: true
        font.pixelSize: CWA.Typo.p2
        color: activeFocus ? CWA.Colors.primary900 : CWA.Colors.shades500
        padding: 4
        width: parent.width - 8
        height: implicitHeight
        placeholderText: "<add name>"
        Keys.onReturnPressed: {
            nameConfirmed(event)
            addCharacterButton.focus = true
        }
        KeyNavigation.tab: addCharacterButton
        KeyNavigation.backtab: root
        wrapMode: TextArea.Wrap
        background: Item {}
    }
    Row {
        id: panelCharactersRow
        anchors.left: parent.left
        anchors.top: name.bottom
        anchors.margins: 8
        spacing: 4
        Repeater {
            id: panelCharactersList
            model: ["first character","second character"]
            delegate: CWM.InlineTextPicButton {
                enabled: false
                text: modelData
            }
        }
        CWM.InlineIconButton {
            id: addCharacterButton
            onClicked: {
                availableCharactersSelector.visible = ! availableCharactersSelector.visible
                availableCharactersSelector.focus = true
            }
            iconContent: "characters"
            KeyNavigation.tab: description
            Keys.onReturnPressed: clicked()
        }
    }
    CWM.InlineSelectionList {
        id: availableCharactersSelector
        anchors.top: panelCharactersRow.bottom
        anchors.left: panelCharactersRow.left
        anchors.topMargin: 8
        visible: false
        onItemClicked: {
            visible = !visible
            description.focus = true
        }
        z: 2
    }
    TextArea {
        id: description
        font.pixelSize: CWA.Typo.p2
        color: activeFocus ? CWA.Colors.primary900 : CWA.Colors.shades500
        anchors.top: panelCharactersRow.bottom
        padding: 4
        width: parent.width - 8
        height: implicitHeight
        placeholderText: "<add description>"
        Keys.onReturnPressed: {
            descriptionConfirmed(event)
            dialogField.focus = true
        }
        Keys.onTabPressed: dialogField.focus = true
        wrapMode: TextArea.Wrap
    }
    Column {
        id: dialogs
        anchors.top: description.bottom
        anchors.topMargin: 4
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
                backgroundColor: dialogField.activeFocus ? CWA.Colors.primary500 : CWA.Colors.shades300
                anchors.verticalCenter: dialogField.verticalCenter
                onClicked: {
                    panelCharactersSelector.visible = ! panelCharactersSelector.visible
                    panelCharactersSelector.focus = true
                }
                iconContent: "dialog"
                enabled: dialogField.displayText !== ""
            }
            TextField {
                id: dialogField
                width: parent.width - 40
                padding: 0
                font.pixelSize: CWA.Typo.p2
                Keys.onReturnPressed: dialogCharacterButton.clicked()
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
    }
    ListView {
        id: panelCharactersSelector
        anchors.top: dialogs.bottom
        x: 40
        spacing: 4
        visible: false
        width: 24 * count
        orientation: ListView.Horizontal
        model: panelCharactersList.model
        currentIndex: 0
        delegate: CWM.InlineTextPicButton {
            size: "S"
            text: modelData
            Keys.onReturnPressed: {
                clicked()
                dialogField.focus = true
            }
            Keys.onTabPressed: panelCharactersSelector.currentIndex < panelCharactersSelector.count-1
                                   ? panelCharactersSelector.currentIndex += 1
                                   : panelCharactersSelector.currentIndex = 0
            Keys.onBacktabPressed: panelCharactersSelector.currentIndex > 0
                                    ? panelCharactersSelector.currentIndex -= 1
                                    : panelCharactersSelector.currentIndex = panelCharactersSelector.count-1
            onClicked: {
                if (dialogField.displayText) {
                    addDialogButtonClicked(modelData, dialogField.displayText)
                    panelCharactersSelector.visible = false
                }
            }
        }
    }
    CWA.P2 {
        id: indexLabel
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 8
        text: "[idx]"
        verticalAlignment: Qt.AlignBottom
        color: CWA.Colors.shades400
    }
}

