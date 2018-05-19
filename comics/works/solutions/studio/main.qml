import QtQuick 2.9
import QtQuick.Window 2.2
import com.cutehacks.gel 1.0
import comics.works.ui.molecules 1.0 as CWM
import comics.works.ui.organisms 1.0 as CWO
import comics.works.ui.templates 1.0 as CWT

Window {
    id: mainWindow
    title: "%1 - %2".arg("comics.works").arg("StoryTeller")
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
        onCharacterAddedToPanel: panelsModel.add(value.panels)
        onDialogAddedToPanel: panelsModel.add(value.panels)
        onCharacterCreated: charactersModel.add(value.characters)
        onCharacterDeleted: {
            charactersModel.clear()
            charactersModel.add(value.characters)
            panelsModel.clear()
            panelsModel.add(value.panels)
        }
        onPanelCreated: panelsModel.add(value.panels)
        onPanelDeleted: {
            panelsModel.clear()
            panelsModel.add(value.panels)
        }
        onPanelDescribed: panelsModel.add(value.panels)
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
    JsonListModel {
        id: panelsModel
        idAttribute: "eid"
    }
    JsonListModel {
        id: charactersModel
        idAttribute: "name"
    }
    CWT.StoryTellerTpl {
        id: storyTellerViewer
        anchors.fill: parent

        charactersList.model: charactersModel
        charactersList.onItemClicked: uc.delete_character(name, workspaceName)
        charactersList.onAddCharacterFieldReturnPressed: {
            uc.create_character(charactersList.addCharacterField.text,workspaceName)
            charactersList.addCharacterField.clear()
        }

        panelsList.model: panelsModel
        panelsList.addPanelButton.onClicked: uc.create_panel("panel"+(panelsModel.count+1), workspaceName)
        panelsList.removePanelButton.onClicked: uc.delete_panel("panel"+(panelsModel.count), workspaceName)

        panelsGrid.model: panelsModel
        panelsGrid.delegate: CWO.PanelCard {
            id: panelCard
            name.text: model.eid
            description.placeholderText: "<%1>".arg(qsTr("add description"))
            description.text: model.description
            onDescriptionConfirmed: uc.describe_panel(model.eid, description.text)
            addCharacterButton.enabled: charactersModel.count > 0
            availableCharactersSelector.model: charactersModel
            availableCharactersSelector.onItemClicked: uc.add_character_to_panel(name, model.eid)
            onAddDialogButtonClicked: uc.add_dialog_to_panel(dialogContent, characterName, model.eid)
            dialogsList.model: model.dialogs
            panelCharactersList.model: model.characters
        }
        saveButton.onClicked: projectJson.saveToJsonDoc()
    }
    CWM.Snackbar {
        id: snackbar
        text: qsTr("hit <b>+</b> to add a panel,<br/><b>-</b> to remove the last created")
        anchors.top: parent.top
        anchors.margins: 16
        anchors.horizontalCenter: parent.horizontalCenter
        Timer {
            id: snackbarTimer
            interval: 2500
            running: true
            onTriggered: parent.visible = false
        }
    }
}
