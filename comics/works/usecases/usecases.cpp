#include <QVariantMap>
#include "usecases.h"
#include "comics/works/entities/workspace/workspace_base.h"
#include "comics/works/entities/panel/panel.h"

using namespace comics::works;

QVariantMap usecases::create_pile(const QString& name, entities::WorkspaceBase* workspace)
{
    if (!workspace->piles().contains(name)) {
        workspace->setPiles(workspace->piles() << name);
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

QVariantMap usecases::create_panel(const QString& name, entities::WorkspaceBase* workspace)
{
    bool found = false;
    for (int i = 0; i < workspace->panels().size(); ++i) {
        if (workspace->panels().at(i)->eid() == name) {
            found = true;
            break;
        }
    }
    if (!found) {
        auto panel = new entities::Panel(name, workspace);
        panel->setWidth(256);
        panel->setHeight(256);
        workspace->addPanel(panel);
        return {
            {"outcome", "PANEL_CREATED"},
            {"eid", name}
        };
    }
    return {
        {"outcome", "PANEL_NOT_CREATED"},
        {"reason", "PANEL_ALREADY_EXISTS"},
        {"eid", name}
    };
}
