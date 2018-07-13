import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../atoms" as CWA
import "../molecules" as CWM
import "../organisms" as CWO

GridLayout {
    id: root
    property alias charactersList: charactersList
    property alias panelsList: panelsList
    property alias panelsGrid: panelsGrid
    property alias saveButton: saveButton
    property alias exportToPdfButton: exportToPdfButton
    property alias openProjectButton: openProjectButton
    property alias closeButton: closeButton
    property alias startProjectHint: startProjectHint
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
                CWA.CWLogoIcon {
                    id: cwLogoIcon
                    width: 40
                }
                Column {
                    anchors.verticalCenter: cwLogoIcon.verticalCenter
                    spacing: -8
                    Row {
                        CWA.H5 {
                            text: "comics."
                            color: CWA.Colors.accent500
                        }
                        CWA.H5 {
                            text: "works"
                            color: CWA.Colors.shades300
                        }
                    }
                    CWA.H5 {
                        text: "StoryTeller"
                        color: CWA.Colors.primary500
                    }

                }
            }
            CWO.CharactersList {
                id: charactersList
                Layout.fillWidth: true
                KeyNavigation.tab: panelsList
            }
            CWO.PanelsList {
                id: panelsList
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: panelsGrid.model
                KeyNavigation.tab: panelsGrid
            }
            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                spacing: 4
                CWM.Button {
                    id: saveButton
                    text: qsTr("Save")
                    width: 52
                }
                CWM.Button {
                    id: closeButton
                    text: qsTr("X")
                    width: 32
                }
                CWM.Button {
                    id: exportToPdfButton
                    text: qsTr("Export PDF")
                    width: 88
                }
            }
        }
    }
    CWM.Desk {
        id: desk
        Layout.fillWidth: true
        Layout.fillHeight: true
        CWO.PanelsGrid {
            id: panelsGrid
            anchors.fill: parent
            anchors.margins: 8
        }
        CWM.Button {
            id: openProjectButton
            text: qsTr("Open Project")
            anchors.centerIn: parent
        }
        CWA.P1 {
            id: startProjectHint
            anchors.top: openProjectButton.bottom
            anchors.topMargin: 16
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("or, start adding characters and panels...")
            color: CWA.Colors.shades300
        }
    }
}
