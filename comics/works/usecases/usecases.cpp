#include <QDebug>
#include <QVariantMap>
#include "usecases.h"
#include "comics/works/entities/register.h"
#include "comics/works/entities/panel/panel.h"
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
        QVariantList panelsList;
        for (int i=0;i<entities_reg->currentWorkspace->panels()->length();i++) {
            QVariantMap panelSerial;
            panelSerial["eid"] = entities_reg->currentWorkspace->panels()->at(i)->eid();
            panelsList << panelSerial;
        }
        ret = {
            {"outcome", "PANEL_CREATED"},
            {"eid", name}
        };
        ret["panels"] = panelsList;
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
        qDebug() << entities_reg->currentWorkspace->panels()->at(i)->eid() << name;
        if (entities_reg->currentWorkspace->panels()->at(i)->eid() == name) {
            entities_reg->currentWorkspace->panels()->remove(i);
            qDebug() << entities_reg->currentWorkspace->panels()->length();
            ret = {
                {"outcome", "PANEL_DELETED"},
                {"eid", name}
            };
            emit panelDeleted(ret);
            break;
        }
    }
    emit usecaseCompleted(ret);
}
