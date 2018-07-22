import QtQuick 2.9
import QtQuick.Window 2.2
import Qt.labs.platform 1.0
import com.cutehacks.gel 1.0
import comics.works.ui.atoms 1.0 as CWA
import comics.works.ui.molecules 1.0 as CWM
import comics.works.ui.organisms 1.0 as CWO
import comics.works.ui.templates 1.0 as CWT

Window {
    id: mainWindow
    title: "%1 %2 - [%3]".arg("comics.works").arg("StoryTeller").arg(projectId)
    visible: true
    width: 1024
    height: 768
    property string projectId
    Component.onCompleted: uc.create_project("project%1".arg(utils.generateRandomId(5)))
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
        onProjectCreated: projectId = value.eid
        onProjectDeleted: {
            projectId = ""
            charactersModel.clear()
            panelsModel.clear()
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
            onItemClicked: uc.delete_character(name, projectId)
            onAddCharacterFieldReturnPressed: {
                if (charactersList.addCharacterField.displayText !== "") {
                    uc.create_character(charactersList.addCharacterField.text, projectId)
                    charactersList.addCharacterField.clear()
                }
            }
        }
        panelsList {
            model: panelsModel
            addPanelButton.onClicked: uc.create_panel("p%1".arg(utils.generateRandomId(5)), projectId)
            onRemovePanelButtonClicked: uc.delete_panel(itemId, projectId)
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
                onDescriptionTabPressed: storyTellerViewer.panelsGrid.currentIndex < storyTellerViewer.panelsGrid.count-1
                                         ? storyTellerViewer.panelsGrid.currentIndex += 1
                                         : storyTellerViewer.panelsGrid.currentIndex = 0
                onDescriptionBacktabPressed: storyTellerViewer.panelsGrid.currentIndex > 0
                                             ? storyTellerViewer.panelsGrid.currentIndex -= 1
                                             : storyTellerViewer.panelsGrid.currentIndex = storyTellerViewer.panelsGrid.count-1
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
        startProjectHint.visible: panelsModel.count === 0 && charactersModel.count === 0
        saveButton {
            onClicked: saveDialog.open()
            enabled: charactersList.model.count > 0 || panelsList.model.count > 0
        }
        exportToPdfButton {
            onClicked: exportToPdfDialog.open()
            enabled: charactersList.model.count > 0 || panelsList.model.count > 0
        }
        closeButton {
            enabled: projectId != "" && (charactersList.model.count > 0 || panelsList.model.count > 0)
            onClicked: uc.delete_project(projectId)
        }
    }
    FileDialog {
        id: saveDialog
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: projectJson.saveToJsonDoc()
        fileMode: FileDialog.SaveFile
        defaultSuffix: "json"
        Connections {
            target: projectJson
            onSaved: {
                var filePath = projectJson.writeJsonToFile(jsonDoc, saveDialog.currentFile)
                snackbar.visible = true
                snackbar.text = qsTr("Project saved to %1".arg(filePath))
                snackbar.timer.start()
            }
        }
    }
    FileDialog {
        id: exportToPdfDialog
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
    CWA.P1 {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        text: storyTellerViewer.panelsGrid.currentIndex
    }
}
