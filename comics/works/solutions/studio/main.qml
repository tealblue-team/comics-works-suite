import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import comics.works.gui.entities 1.0 as CWE

Window {
    id: mainWindow
    visible: true
    width: 256 * 3 + 48
    height: 600
    Component.onCompleted: uc.create_workspace("workspace1")
    Connections {
        target: uc
        onWorkspaceCreated: mainWindow.title = value.eid
        onPanelCreated: rep.model = value.panels
    }
    CWE.Workspace {
        columns: 3
        anchors.fill: parent
        Repeater {
            id: rep
            model: []
            delegate: CWE.Panel {
                panelName.text: modelData.eid
            }
        }
    }
    Button {
        id: addPanelButton
        anchors.margins: 8
        anchors.top: parent.top
        anchors.right: parent.right
        text: "+"
        width: 40
        height: width
        onClicked: uc.create_panel("panel"+(rep.model.length+1),"defaultWorkspace")
    }
    Button {
        id: removePanelButton
        anchors.margins: 8
        anchors.top: addPanelButton.bottom
        anchors.right: parent.right
        text: "-"
        width: 40
        height: width
        onClicked: uc.delete_panel("panel1","defaultWorkspace")
    }
}
