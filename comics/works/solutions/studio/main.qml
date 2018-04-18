import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import comics.works.gui.entities 1.0 as CWGE

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
        onPanelDeleted: rep.model = value.panels
        onPanelDescribed: rep.model = value.panels
    }
    CWGE.Workspace {
        columns: 3
        anchors.fill: parent
        Repeater {
            id: rep
            model: []
            delegate: CWGE.Panel {
                name.text: modelData.eid
                description.placeholderText: modelData.description || "<add description>"
                Keys.onReturnPressed: uc.describe_panel(modelData.eid, description.displayText)
            }
        }
    }
    Button {
        id: addPanelButton
        onClicked: uc.create_panel("panel"+(rep.model.length+1),"workspace1")
        anchors.margins: 8
        anchors.top: parent.top
        anchors.right: parent.right
        text: "+"
        width: 40
        height: width
    }
    Button {
        id: removePanelButton
        onClicked: uc.delete_panel("panel"+(rep.model.length),"workspace1")
        anchors.margins: 8
        anchors.top: addPanelButton.bottom
        anchors.right: parent.right
        text: "-"
        width: 40
        height: width
        enabled: rep.model.length > 0
    }
    ListView {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 200
        height: 400
        model: rep.model
        delegate: Text {
            text: modelData.description
        }
    }
}
