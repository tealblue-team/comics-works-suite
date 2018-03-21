#ifndef USECASES_H
#define USECASES_H
#include <QVariantMap>
class QString;

namespace comics {
namespace works {
namespace entities {
class Workspace;
}
namespace usecases {
QVariantMap create_pile_with_name(const QString& name, entities::Workspace *workspace);
}
}
}

#endif // USECASES_H
