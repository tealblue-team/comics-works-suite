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
    if (!entities_reg->workspace->piles().contains(name)) {
        entities_reg->workspace->setPiles(entities_reg->workspace->piles() << name);
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

QVariantMap usecases::create_panel(const QString& name, const QString& workspaceName)
{
    bool found = false;
    for (int i = 0; i < entities_reg->workspace->panels().size(); ++i) {
        if (entities_reg->workspace->panels().at(i)->eid() == name) {
            found = true;
            break;
        }
    }
    if (!found) {
        auto panel = new entities::Panel(name, entities_reg->workspace);
        panel->setWidth(256);
        panel->setHeight(256);
        entities_reg->workspace->addPanel(panel);
        QVariantList panelsList;
        for (int i=0;i<entities_reg->workspace->panels().length();i++) {
            QVariantMap panelSerial = QVariantMap();
            panelSerial["eid"] = entities_reg->workspace->panels().at(i)->eid();
            panelsList << panelSerial;
        }
        QVariantMap ret({
                            {"outcome", "PANEL_CREATED"},
                            {"eid", name}
                        });
        ret["panels"] = panelsList;
        return ret;
    }
    return {
        {"outcome", "PANEL_NOT_CREATED"},
        {"reason", "PANEL_ALREADY_EXISTS"},
        {"eid", name}
    };
}

Q_INVOKABLE QVariantMap create_workspace(const QString& name)
{
    entities_reg->workspace = new entities::Workspace(name);
    return {
        {"outcome", "WORKSPACE_NOT_CREATED"},
        {"reason", "NOT_IMPLEMENTED"},
        {"eid", name}
    };
}
