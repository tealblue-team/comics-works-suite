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

void usecases::create_panel(const QString& name, const QString& workspaceName)
{
    QVariantMap ret;
    bool found = false;
    for (int i = 0; i < entities_reg->currentWorkspace->panels()->size(); ++i) {
        if (entities_reg->currentWorkspace->panels()->at(i)->eid() == name) {
            found = true;
            break;
        }
    }
    if (!found) {
        auto panel = new entities::Panel(name, entities_reg->currentWorkspace);
        panel->setWidth(256);
        panel->setHeight(256);
        entities_reg->currentWorkspace->addPanel(panel);
        ret = {
            {"outcome", "PANEL_CREATED"},
            {"eid", name},
            {"panels", _getPanelsList(entities_reg->currentWorkspace->panels())}
        };
        emit panelCreated(ret);
    } else {
        ret = {
            {"outcome", "PANEL_NOT_CREATED"},
            {"reason", "PANEL_ALREADY_EXISTS"},
            {"eid", name}
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

void usecases::delete_panel(const QString &name, const QString &workspaceName)
{
    QVariantMap ret;
    for (int i=0;i<entities_reg->currentWorkspace->panels()->length();i++) {
        if (entities_reg->currentWorkspace->panels()->at(i)->eid() == name) {
            entities_reg->currentWorkspace->panels()->remove(i);
            break;
        }
    }
    ret = {
        {"outcome", "PANEL_DELETED"},
        {"eid", name},
        {"panels", _getPanelsList(entities_reg->currentWorkspace->panels())}
    };
    emit panelDeleted(ret);
    emit usecaseCompleted(ret);
}

void usecases::describe_panel(const QString &name, const QString &description)
{
    QVariantMap ret;
    for (int i=0;i<entities_reg->currentWorkspace->panels()->length();i++) {
        if (entities_reg->currentWorkspace->panels()->at(i)->eid() == name) {
            entities_reg->currentWorkspace->panels()->at(i)->setDescription(description);
            break;
        }
    }
    ret = {
        {"outcome", "PANEL_DESCRIBED"},
        {"eid", name},
        {"panels", _getPanelsList(entities_reg->currentWorkspace->panels())}
    };
    emit panelDescribed(ret);
    emit usecaseCompleted(ret);
}

QVariantList usecases::_getPanelsList(QVector<entities::PanelBase *>* panels) const
{
    QVariantList panelsList;
    for (int i=0;i<panels->length();i++) {
        QVariantMap panelSerial;
        panelSerial["eid"] = panels->at(i)->eid();
        panelSerial["description"] = panels->at(i)->description();
        panelsList << panelSerial;
    }
    return panelsList;
}

QVariantList usecases::_getCharactersList(QVector<entities::CharacterBase *>* characters) const
{
    QVariantList charactersList;
    for (int i=0;i<characters->length();i++) {
        QVariantMap characterSerial;
        characterSerial["name"] = characters->at(i)->name();
        charactersList << characterSerial;
    }
    return charactersList;
}
