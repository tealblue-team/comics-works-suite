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
                id: charactersList
                Layout.fillWidth: true
            }
            CWO.PanelsList {
                id: panelsList
                Layout.fillHeight: true
                Layout.fillWidth: true
                model: panelsGrid.model
            }
            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                spacing: 8
                Button {
                    id: saveButton
                    text: qsTr("Save")
                    width: 64
                }
                Button {
                    id: exportToPdfButton
                    text: qsTr("Export PDF")
                    width: 88
                }
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
            CWO.PanelsGrid {
                id: panelsGrid
                anchors.fill: parent
                anchors.margins: 8
            }
            Button {
                id: openProjectButton
                text: qsTr("open project")
                anchors.centerIn: parent
            }
        }
    }
}
