#ifndef USECASES_H
#define USECASES_H
#include <QVariantMap>
class QString;
#include "comics/works/entities/workspace/workspace_base.h"

namespace comics {
namespace works {
namespace usecases {
QVariantMap create_pile(const QString& name, entities::WorkspaceBase *workspace);
QVariantMap create_panel(const QString& name, entities::WorkspaceBase *workspace);
}
}
}

#endif // USECASES_H
