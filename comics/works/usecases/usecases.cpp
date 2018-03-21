#include <QVariantMap>
#include "usecases.h"
#include "comics/works/entities/workspace/workspace.h"

using namespace comics::works;

QVariantMap usecases::create_pile_with_name(const QString& name, entities::Workspace* workspace)
{
    if (!workspace->panels().contains(name)) {
        workspace->setPanels(workspace->panels() << name);
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
