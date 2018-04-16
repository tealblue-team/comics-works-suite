import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import comics.works.gui.entities 1.0
import comics.works.gui.templates 1.0

Window {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    Component.onCompleted: uc.create_workspace("defaultWorspace")
    Connections {
        target: uc
        onWorkspaceCreated: mainWindow.title = value.eid
        onPanelCreated: rep.model = value.panels
    }
    Workspace {
        id: panelFocusViewer
        anchors.fill: parent
        Repeater {
            id: rep
            model: []
            delegate: Panel {
                panelName.text: modelData.eid
            }
        }
    }
    Button {
        anchors.margins: 8
        anchors.top: parent.top
        anchors.right: parent.right
        text: "+"
        width: 40
        height: width
        onClicked: uc.create_panel("panel"+(rep.model.length+1),"defaultWorkspace")
    }
}
