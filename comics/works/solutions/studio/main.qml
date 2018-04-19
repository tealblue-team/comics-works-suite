import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import comics.works.gui.atoms 1.0 as CWGA
import comics.works.gui.molecules 1.0 as CWGM

Window {
    id: mainWindow
    visible: true
    width: 256 * 3 + 48 + 200
    height: 600
    property string workspaceName: "workspace1"
    Component.onCompleted: uc.create_workspace(workspaceName)
    Connections {
        target: uc
        onWorkspaceCreated: mainWindow.title = value.eid
        onPanelCreated: rep.model = value.panels
        onPanelDeleted: rep.model = value.panels
        onPanelDescribed: rep.model = value.panels
    }
    GridLayout {
        anchors.fill: parent
        columnSpacing: 0
        Rectangle {
            color: "#333"
            Layout.preferredWidth: 200
            Layout.fillHeight: true
            ListView {
                anchors.fill: parent
                anchors.margins: 16
                model: rep.model
                delegate: Column {
                    Text {
                        text: modelData.eid
                        color: "white"
                        opacity: .8
                    }
                    Text {
                        x: 16
                        text: modelData.description
                        color: "white"
                    }
                }
            }
            CWGA.CWLogo {
                anchors.bottom: parent.bottom
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
            CWGM.Table {
                columns: 3
                anchors.fill: parent
                Repeater {
                    id: rep
                    model: []
                    delegate: CWGM.PanelCard {
                        name.text: modelData.eid
                        description.placeholderText: modelData.description || "<add description>"
                        Keys.onReturnPressed: uc.describe_panel(modelData.eid, description.displayText)
                    }
                }
            }
            Button {
                id: addPanelButton
                onClicked: uc.create_panel("panel"+(rep.model.length+1), workspaceName)
                anchors.margins: 8
                anchors.top: parent.top
                anchors.right: parent.right
                text: "+"
                width: 40
                height: width
            }
            Button {
                id: removePanelButton
                onClicked: uc.delete_panel("panel"+(rep.model.length), workspaceName)
                anchors.margins: 8
                anchors.top: addPanelButton.bottom
                anchors.right: parent.right
                text: "-"
                width: 40
                height: width
                enabled: rep.model.length > 0
            }
        }
    }
}
