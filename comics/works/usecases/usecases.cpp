#include <QDebug>
#include <QVariantMap>
#include "usecases.h"
#include "comics/works/entities/register.h"
#include "comics/works/entities/panel/panel.h"
#include "comics/works/entities/character/character.h"
#include "comics/works/entities/project/project.h"

using namespace comics::works;

usecases::usecases(QObject *parent) : QObject(parent)
{}

void usecases::add_character_to_panel(const QString &characterName, const QString &panelName)
{
    QVariantMap ret;
    entities::PanelBase* panel = nullptr;
    entities::CharacterBase* character = nullptr;
    auto panels = entities_reg->currentProject->panels();
    for (int i=0;i<panels->length();++i) {
        panel = panels->at(i);
        if (panel->eid() == panelName) {
            auto characters = entities_reg->currentProject->characters();
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
        {"panels", _getPanelsList(entities_reg->currentProject->panels())}
    };
    emit characterAddedToPanel(ret);
    emit usecaseCompleted(ret);
}

void usecases::add_dialog_to_panel(const QString &dialogId, const QString &dialogContent, const QString &characterName, const QString &panelName)
{
    QVariantMap ret;
    entities::PanelBase* panel;
    for (int i=0;i<entities_reg->currentProject->panels()->length();++i) {
        if (entities_reg->currentProject->panels()->at(i)->eid() == panelName) {
            panel = entities_reg->currentProject->panels()->at(i);
            panel->addDialog(dialogId, dialogContent, characterName);
            break;
        }
    }
    ret = {
        {"outcome", "DIALOG_ADDED_TO_PANEL"},
        {"dialogContent_en_US", dialogContent},
        {"characterName", characterName},
        {"panelName", panel->eid()},
        {"panels", _getPanelsList(entities_reg->currentProject->panels())}
    };
    emit dialogAddedToPanel(ret);
    emit usecaseCompleted(ret);
}

QVariantMap usecases::create_pile(const QString& name, const QString& ProjectName)
{
    if (!entities_reg->currentProject->piles().contains(name)) {
        entities_reg->currentProject->setPiles(entities_reg->currentProject->piles() << name);
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

void usecases::create_panel(const QString& eid, const QString& ProjectName)
{
    QVariantMap ret;
    bool found = false;
    auto panels = entities_reg->currentProject->panels();
    for (int i = 0; i < panels->size(); ++i) {
        if (panels->at(i)->eid() == eid) {
            found = true;
            break;
        }
    }
    if (!found) {
        auto panel = new entities::Panel(eid, entities_reg->currentProject);
        panel->setWidth(256);
        panel->setHeight(256);
        entities_reg->currentProject->addPanel(panel);
        ret = {
            {"outcome", "PANEL_CREATED"},
            {"eid", eid},
            {"panels", _getPanelsList(entities_reg->currentProject->panels())}
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

void usecases::create_character(const QString& name, const QString& ProjectName)
{
    QVariantMap ret;
    bool found = false;
    for (int i = 0; i < entities_reg->currentProject->characters()->size(); ++i) {
        if (entities_reg->currentProject->characters()->at(i)->name() == name) {
            found = true;
            break;
        }
    }
    if (!found) {
        auto character = new entities::Character(name, entities_reg->currentProject);
        entities_reg->currentProject->addCharacter(character);
        ret = {
            {"outcome", "CHARACTER_CREATED"},
            {"name", name},
            {"characters", _getCharactersList(entities_reg->currentProject->characters())}
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

Q_INVOKABLE void usecases::create_project(const QString& name)
{
    QVariantMap ret;
    entities_reg->currentProject = new entities::Project(name);
    ret = {
        {"outcome", "Project_CREATED"},
        {"eid", name}
    };
    emit usecaseCompleted(ret);
    emit projectCreated(ret);
}

void usecases::delete_character(const QString &characterName, const QString &ProjectName)
{
    QVariantMap ret;
    auto characters = entities_reg->currentProject->characters();
    for (int i=0;i<characters->length();++i) {
        if (characters->at(i)->name() == characterName) {
            characters->remove(i);
            break;
        }
    }
    auto panels = entities_reg->currentProject->panels();
    for (int i=0;i<panels->length();++i) {
        auto dialogs = panels->at(i)->dialogs();
        if (dialogs.size() > 0) {
            for (int j=0;j<dialogs.size();++j) {
                auto dialog = dialogs.at(j).toMap();
                if (dialog.value("characterName").toString() == characterName) {
                    panels->at(i)->removeDialog(dialog.value("dialogId").toString());
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
        {"characters", _getCharactersList(entities_reg->currentProject->characters())},
        {"panels", _getPanelsList(entities_reg->currentProject->panels())}
    };
    emit characterDeleted(ret);
    emit usecaseCompleted(ret);
}

void usecases::delete_panel(const QString &name, const QString &ProjectName)
{
    QVariantMap ret;
    auto panels = entities_reg->currentProject->panels();
    for (int i=0;i<panels->size();++i) {
        if (panels->at(i)->eid() == name) {
            panels->remove(i);
            break;
        }
    }
    ret = {
        {"outcome", "PANEL_DELETED"},
        {"eid", name},
        {"panels", _getPanelsList(entities_reg->currentProject->panels())}
    };
    emit panelDeleted(ret);
    emit usecaseCompleted(ret);
}

void usecases::delete_dialog_from_panel(const QString &dialogId, const QString &panelId, const QString &ProjectName)
{
    qDebug() << "here";
    QVariantMap ret;
    auto panels = entities_reg->currentProject->panels();
    for (auto panel : *panels) {
        if (panel->eid() == panelId) {
            for (auto dialog : panel->dialogs()) {
                qDebug() << "dialog";
                if (dialog.toMap().value("dialogId").toString() == dialogId) {
                    panel->removeDialog(dialog.toMap().value("dialogId").toString());
                    break;
                }
            }
        }
    }
    ret = {
        {"outcome", "DIALOG_DELETED_FROM_PANEL"},
        {"eid", dialogId},
        {"panels", _getPanelsList(entities_reg->currentProject->panels())}
    };
    emit dialogDeletedFromPanel(ret);
    emit usecaseCompleted(ret);
}

void usecases::delete_project(const QString &name)
{
    QVariantMap ret;
    if (name == entities_reg->currentProject->eid()) {
        delete entities_reg->currentProject;
        entities_reg->currentProject = nullptr;
    }
    ret = {
        {"outcome", "PROJECT_DELETED"},
        {"eid", name},
        {"characters", QStringList()},
        {"panels", QStringList()}
    };
    emit projectDeleted(ret);
    emit usecaseCompleted(ret);
}

void usecases::describe_panel(const QString &panelId, const QString &panelDescription)
{
    QVariantMap ret;
    for (int i=0;i<entities_reg->currentProject->panels()->length();++i) {
        if (entities_reg->currentProject->panels()->at(i)->eid() == panelId) {
            entities_reg->currentProject->panels()->at(i)->setDescription(panelDescription);
            break;
        }
    }
    ret = {
        {"outcome", "PANEL_DESCRIBED"},
        {"eid", panelId},
        {"panels", _getPanelsList(entities_reg->currentProject->panels())}
    };
    emit panelDescribed(ret);
    emit usecaseCompleted(ret);
}

void usecases::name_panel(const QString &panelId, const QString &panelName)
{
    QVariantMap ret;
    auto panels = entities_reg->currentProject->panels();
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

void usecases::name_project(const QString &projectId, const QString &projectName)
{
    QVariantMap ret;
    entities_reg->currentProject->setName(projectName);
    ret = {
        {"outcome", "PROJECT_NAMED"},
        {"eid", projectId},
        {"name", projectName}
    };
    emit projectNamed(ret);
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
