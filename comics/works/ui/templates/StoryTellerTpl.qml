import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../atoms" as CWA
import "../molecules" as CWM
import "../organisms" as CWO

FocusScope {
    id: root
    property alias charactersList: charactersList
    property alias panelsList: panelsList
    property alias panelsGrid: panelsGrid
    property alias saveButton: saveButton
    property alias projectNameLabel: projectNameLabel
    property alias exportToPdfButton: exportToPdfButton
    property alias openProjectButton: openProjectButton
    property alias closeButton: closeButton
    property alias startProjectHint: startProjectHint
    width: 1024
    height: 768
    GridLayout {
        anchors.fill: parent
        columnSpacing: 0
        Rectangle {
            color: CWA.Colors.shades600
            Layout.preferredWidth: 200
            Layout.fillHeight: true
            ColumnLayout {
                id: entityListsColumn
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: projectNameLabel.top
                anchors.margins: 16
                anchors.topMargin: 8
                CWM.AppBadge {
                    Layout.fillWidth: true
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
                    KeyNavigation.tab: projectNameLabel
                }
            }
            CWM.ProjectNameLabel {
                id: projectNameLabel
                anchors.bottom: projectButtons.top
                width: parent.width
                x: 16
                KeyNavigation.tab: panelsGrid
            }
            Row {
                id: projectButtons
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                spacing: 4
                anchors.margins: 16
                CWM.Button {
                    id: saveButton
                    text: qsTr("Save")
                    width: 48
                }
                CWM.Button {
                    id: closeButton
                    text: qsTr("X")
                    width: 28
                }
                CWM.Button {
                    id: exportToPdfButton
                    text: qsTr("Export PDF")
                    width: 84
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
                text: qsTr("Or, start adding characters and panels...")
                color: CWA.Colors.shades300
            }
        }
    }
}
