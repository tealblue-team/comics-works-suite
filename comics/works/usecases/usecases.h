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
    Q_INVOKABLE void create_panel(const QString& name, const QString& workspaceName);
    Q_INVOKABLE QVariantMap create_pile(const QString& name, const QString& workspaceName);
    Q_INVOKABLE void create_workspace(const QString& name);
    entities::Register* entities_reg = nullptr;
signals:
    void panelCreated(QVariantMap value);
    void panelNotCreated(QVariantMap value);
    void workspaceCreated(QVariantMap value);
};
}
}

#endif // USECASES_H
