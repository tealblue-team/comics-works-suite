#include <QDebug>
#include <QVariantMap>
#include "usecases.h"
#include "comics/works/entities/register.h"
#include "comics/works/entities/panel/panel.h"
#include "comics/works/entities/character/character.h"
#include "comics/works/entities/workspace/workspace.h"

using namespace comics::works;

usecases::usecases(QObject *parent) : QObject(parent)
{}

void usecases::add_character_to_panel(const QString &characterName, const QString &panelName)
{
    QVariantMap ret;
    entities::PanelBase* panel = nullptr;
    entities::CharacterBase* character = nullptr;
    auto panels = entities_reg->currentWorkspace->panels();
    for (int i=0;i<panels->length();++i) {
        panel = panels->at(i);
        if (panel->eid() == panelName) {
            auto characters = entities_reg->currentWorkspace->characters();
            for (int j=0;j<characters->length();++j) {
                character = characters->at(j);
                if (character->name() == characterName) {
                    panel->addCharacter(character);
                    break;
                }
            }
            break;
        }
    }
    ret = {
        {"outcome", "CHARACTER_ADDED_TO_PANEL"},
        {"characterName", character->name()},
        {"panelName", panel->eid()},
        {"panels", _getPanelsList(entities_reg->currentWorkspace->panels())}
    };
    emit characterAddedToPanel(ret);
    emit usecaseCompleted(ret);
}

void usecases::add_dialog_to_panel(const QString &dialogContent, const QString &characterName, const QString &panelName)
{
    QVariantMap ret;
    entities::PanelBase* panel;
    for (int i=0;i<entities_reg->currentWorkspace->panels()->length();++i) {
        if (entities_reg->currentWorkspace->panels()->at(i)->eid() == panelName) {
            panel = entities_reg->currentWorkspace->panels()->at(i);
            panel->addDialog(dialogContent, characterName);
            break;
        }
    }
    ret = {
        {"outcome", "DIALOG_ADDED_TO_PANEL"},
        {"dialogContent_en_US", dialogContent},
        {"characterName", characterName},
        {"panelName", panel->eid()},
        {"panels", _getPanelsList(entities_reg->currentWorkspace->panels())}
    };
    emit dialogAddedToPanel(ret);
    emit usecaseCompleted(ret);
}

QVariantMap usecases::create_pile(const QString& name, const QString& workspaceName)
{
    if (!entities_reg->currentWorkspace->piles().contains(name)) {
        entities_reg->currentWorkspace->setPiles(entities_reg->currentWorkspace->piles() << name);
        return {
            {"outcome", "PILE_CREATED"},
            {"eid", name}
        };
    }
    return {
        {"outcome", "PILE_NOT_CREATED"},
        {"reason", "PILE_ALREADY_EXISTS"},
        {"eid", name}
    };
}

void usecases::create_panel(const QString& eid, const QString& workspaceName)
{
    QVariantMap ret;
    bool found = false;
    auto panels = entities_reg->currentWorkspace->panels();
    for (int i = 0; i < panels->size(); ++i) {
        if (panels->at(i)->eid() == eid) {
            found = true;
            break;
        }
    }
    if (!found) {
        auto panel = new entities::Panel(eid, entities_reg->currentWorkspace);
        panel->setWidth(256);
        panel->setHeight(256);
        entities_reg->currentWorkspace->addPanel(panel);
        ret = {
            {"outcome", "PANEL_CREATED"},
            {"eid", eid},
            {"panels", _getPanelsList(entities_reg->currentWorkspace->panels())}
        };
        emit panelCreated(ret);
    } else {
        ret = {
            {"outcome", "PANEL_NOT_CREATED"},
            {"reason", "PANEL_ALREADY_EXISTS"},
            {"eid", eid}
        };
        emit panelNotCreated(ret);
    }
    emit usecaseCompleted(ret);
}

void usecases::create_character(const QString& name, const QString& workspaceName)
{
    QVariantMap ret;
    bool found = false;
    for (int i = 0; i < entities_reg->currentWorkspace->characters()->size(); ++i) {
        if (entities_reg->currentWorkspace->characters()->at(i)->name() == name) {
            found = true;
            break;
        }
    }
    if (!found) {
        auto character = new entities::Character(name, entities_reg->currentWorkspace);
        entities_reg->currentWorkspace->addCharacter(character);
        ret = {
            {"outcome", "CHARACTER_CREATED"},
            {"name", name},
            {"characters", _getCharactersList(entities_reg->currentWorkspace->characters())}
        };
        emit characterCreated(ret);
    } else {
        ret = {
            {"outcome", "CHARACTER_NOT_CREATED"},
            {"reason", "CHARACTER_ALREADY_EXISTS"},
            {"name", name}
        };
        emit characterNotCreated(ret);
    }
    emit usecaseCompleted(ret);
}

Q_INVOKABLE void usecases::create_workspace(const QString& name)
{
    QVariantMap ret;
    entities_reg->currentWorkspace = new entities::Workspace(name);
    ret = {
        {"outcome", "WORKSPACE_CREATED"},
        {"eid", name}
    };
    emit usecaseCompleted(ret);
    emit workspaceCreated(ret);
}

void usecases::delete_character(const QString &characterName, const QString &workspaceName)
{
    QVariantMap ret;
    auto characters = entities_reg->currentWorkspace->characters();
    for (int i=0;i<characters->length();++i) {
        if (characters->at(i)->name() == characterName) {
            characters->remove(i);
            break;
        }
    }
    auto panels = entities_reg->currentWorkspace->panels();
    for (int i=0;i<panels->length();++i) {
        auto dialogs = panels->at(i)->dialogs();
        if (dialogs.size() > 0) {
            for (int j=0;j<dialogs.size();++j) {
                auto dialog = dialogs.at(j).toMap();
                if (dialog.value("characterName").toString() == characterName) {
                    panels->at(i)->removeDialog(
                                dialog.value("dialogContent_en_US").toString(),
                                dialog.value("characterName").toString());
                }
            }
        }
        auto dialogCharacters = panels->at(i)->characters();
        if (dialogCharacters->size() > 0) {
            for (int j=0;j<dialogCharacters->size();++j) {
                if (dialogCharacters->at(j)->name() == characterName) {
                    dialogCharacters->remove(j);
                    break;
                }
            }
        }
    }
    ret = {
        {"outcome", "CHARACTER_DELETED"},
        {"name", characterName},
        {"characters", _getCharactersList(entities_reg->currentWorkspace->characters())},
        {"panels", _getPanelsList(entities_reg->currentWorkspace->panels())}
    };
    emit characterDeleted(ret);
    emit usecaseCompleted(ret);
}

void usecases::delete_panel(const QString &name, const QString &workspaceName)
{
    QVariantMap ret;
    auto panels = entities_reg->currentWorkspace->panels();
    for (int i=0;i<panels->size();++i) {
        if (panels->at(i)->eid() == name) {
            panels->remove(i);
            break;
        }
    }
    ret = {
        {"outcome", "PANEL_DELETED"},
        {"eid", name},
        {"panels", _getPanelsList(panels)}
    };
    emit panelDeleted(ret);
    emit usecaseCompleted(ret);
}

void usecases::describe_panel(const QString &panelId, const QString &panelDescription)
{
    QVariantMap ret;
    for (int i=0;i<entities_reg->currentWorkspace->panels()->length();++i) {
        if (entities_reg->currentWorkspace->panels()->at(i)->eid() == panelId) {
            entities_reg->currentWorkspace->panels()->at(i)->setDescription(panelDescription);
            break;
        }
    }
    ret = {
        {"outcome", "PANEL_DESCRIBED"},
        {"eid", panelId},
        {"panels", _getPanelsList(entities_reg->currentWorkspace->panels())}
    };
    emit panelDescribed(ret);
    emit usecaseCompleted(ret);
}

void usecases::name_panel(const QString &panelId, const QString &panelName)
{
    QVariantMap ret;
    auto panels = entities_reg->currentWorkspace->panels();
    for (int i=0;i<panels->length();++i) {
        if (panels->at(i)->eid() == panelId) {
            panels->at(i)->setName(panelName);
            break;
        }
    }
    ret = {
        {"outcome", "PANEL_NAMED"},
        {"eid", panelId},
        {"panels", _getPanelsList(panels)}
    };
    emit panelNamed(ret);
    emit usecaseCompleted(ret);
}

// ----------------------------------------------------------------------------------

QVariantList usecases::_getPanelsList(QVector<entities::PanelBase *>* panels) const
{
    QVariantList panelsList;
    for (int i=0;i<panels->length();++i) {
        QVariantMap panelSerial;
        panelSerial["eid"] = panels->at(i)->eid();
        panelSerial["name"] = panels->at(i)->name();
        panelSerial["description"] = panels->at(i)->description();
        QVariantList characters;
        for (int j=0;j<panels->at(i)->characters()->length();++j) {
            characters << panels->at(i)->characters()->at(j)->name();
        }
        panelSerial["characters"] = characters;
        panelSerial["dialogs"] = QVariantList(panels->at(i)->dialogs());
        panelsList << panelSerial;
    }
    return panelsList;
}

QVariantList usecases::_getCharactersList(QVector<entities::CharacterBase *>* characters) const
{
    QVariantList charactersList;
    if (characters->length() > 0) {
        for (int i=0;i<characters->length();++i) {
            QVariantMap characterSerial;
            characterSerial["name"] = characters->at(i)->name();
            charactersList << characterSerial;
        }
    }
    return charactersList;
}
