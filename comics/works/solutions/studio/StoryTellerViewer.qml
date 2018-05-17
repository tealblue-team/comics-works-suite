import comics.works.ui.templates 1.0 as CWT

CWT.StoryTellerTpl {
    charactersListView.onItemClicked: uc.delete_character(name, workspaceName)
}
