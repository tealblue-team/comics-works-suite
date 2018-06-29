import QtQuick 2.9
import QtQuick.Window 2.2
import Qt.labs.platform 1.0
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
    property string projectName: "project1"
    Component.onCompleted: uc.create_project(projectName)
    Connections {
        target: uc
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
        onPanelNamed: panelsModel.add(value.panels)
    }
    Connections {
        target: projectJson
        onSaved: {
            projectJson.writeJsonToFile(jsonDoc,"../../heavyLoad1.cw.json")
            snackbar.visible = true
            snackbar.text = qsTr("File saved")
            snackbar.timer.start()
        }
    }
    Connections {
        target: projectPdf
        onSaved: {
            snackbar.visible = true
            snackbar.text = qsTr("Project exported to %1".arg(filePath))
            snackbar.timer.start()
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
        charactersList {
            model: charactersModel
            onItemClicked: uc.delete_character(name, projectName)
            onAddCharacterFieldReturnPressed: {
                uc.create_character(charactersList.addCharacterField.text,projectName)
                charactersList.addCharacterField.clear()
            }
        }
        panelsList {
            model: panelsModel
            addPanelButton.onClicked: {
                var abc=["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
                uc.create_panel("panel%1%2%3%4%5"
                                .arg(abc[Math.floor(Math.random()*26)].toUpperCase())
                                .arg(abc[Math.floor(Math.random()*26)].toUpperCase())
                                .arg(abc[Math.floor(Math.random()*26)].toUpperCase())
                                .arg(abc[Math.floor(Math.random()*26)].toUpperCase())
                                .arg(abc[Math.floor(Math.random()*26)].toUpperCase()), projectName)
            }
            onRemovePanelButtonClicked: uc.delete_panel(itemId, projectName)
        }
        panelsGrid {
            model: panelsModel
            delegate: CWO.PanelCard {
                id: panelCard
                name.placeholderText: "[%1]".arg(model.eid)
                name.text: model.name || ""
                description.placeholderText: qsTr("add description...")
                description.text: model.description
                onNameConfirmed: uc.name_panel(model.eid, name.text)
                onDescriptionConfirmed: uc.describe_panel(model.eid, description.text)
                addCharacterButton.enabled: charactersModel.count > 0
                availableCharactersSelector.model: charactersModel
                availableCharactersSelector.onItemClicked: uc.add_character_to_panel(name, model.eid)
                onAddDialogButtonClicked: {
                    uc.add_dialog_to_panel(dialogContent, characterName, model.eid)
                    dialogField.clear()
                }
                dialogsList.model: model.dialogs
                panelCharactersList.model: model.characters
                indexLabel.text: 1+index
            }
        }
        openProjectButton {
            onClicked: openDialog.open()
            visible: panelsModel.count === 0 && charactersModel.count === 0
        }
        saveButton {
            onClicked: projectJson.saveToJsonDoc()
        }
        exportToPdfButton {
            onClicked: saveDialog.open()
            enabled: charactersList.model.count > 0 || panelsList.model.count > 0
        }
    }
    FileDialog {
        id: saveDialog
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: projectPdf.saveToPdf(file)
        fileMode: FileDialog.SaveFile
        defaultSuffix: "pdf"
    }
    FileDialog {
        id: openDialog
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            var jsonString = projectJson.readJsonFromFile(file)
            projectJson.loadFromJsonDoc(jsonString)
        }
        fileMode: FileDialog.OpenFile
        nameFilters: ["CW JSON files (*.cw.json)"]
    }
    CWM.Snackbar {
        id: snackbar
        text: qsTr("hit <b>+</b> to add a panel,<br/><b>-</b> to remove the last created")
        anchors.top: parent.top
        anchors.margins: 16
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
