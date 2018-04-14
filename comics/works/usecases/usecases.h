#ifndef USECASES_H
#define USECASES_H
#include <QVariantMap>
class QString;
#include "comics/works/entities/register.h"

namespace comics {
namespace works {
class usecases : public QObject {
    Q_OBJECT
public:
    explicit usecases(QObject* parent = nullptr);
    Q_INVOKABLE QVariantMap create_panel(const QString& name, const QString& workspaceName);
    Q_INVOKABLE QVariantMap create_pile(const QString& name, const QString& workspaceName);
    Q_INVOKABLE QVariantMap create_workspace(const QString& name);
    entities::Register* entities_reg;
};
}
}

#endif // USECASES_H
