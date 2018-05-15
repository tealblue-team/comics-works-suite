import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: mainWindow
    title: "comics.works StoryTeller"
    visible: true
    width: 1024
    height: 768
    property string workspaceName: "workspace1"
    Component.onCompleted: uc.create_workspace(workspaceName)
    Connections {
        target: uc
        onWorkspaceCreated: {
            var jsonString = projectJson.readJsonFromFile("../../heavyLoad1.cw.json")
            projectJson.loadFromJsonDoc(jsonString)
        }
        onCharacterAddedToPanel: storyTellerViewer.panelsGrid.model = value.panels
        onDialogAddedToPanel: storyTellerViewer.panelsGrid.model = value.panels
        onCharacterCreated: storyTellerViewer.charactersListView.model = value.characters
        onCharacterDeleted: {
            storyTellerViewer.charactersListView.model = value.characters
            storyTellerViewer.panelsGrid.model = value.panels
        }
        onPanelCreated: storyTellerViewer.panelsGrid.model = value.panels
        onPanelDeleted: storyTellerViewer.panelsGrid.model = value.panels
        onPanelDescribed: storyTellerViewer.panelsGrid.model = value.panels
    }
    Connections {
        target: projectJson
        onSaved: {
            projectJson.writeJsonToFile(jsonDoc,"../../heavyLoad1.cw.json")
            snackbar.visible = true
            snackbar.text = qsTr("File saved")
            snackbarTimer.start()
        }
    }
    StoryTellerViewer {
        id: storyTellerViewer
        anchors.fill: parent
    }
}
