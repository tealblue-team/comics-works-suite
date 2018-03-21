#ifndef WORKSPACE_H
#define WORKSPACE_H
#include "workspace_base.h"

#include <QObject>

namespace comics {
namespace works {
namespace entities {
class Workspace : public WorkspaceBase
{
    Q_OBJECT
public:
    explicit Workspace(const QString& eid, QObject *parent = nullptr);
    QString eid() const;
    QStringList panels() const;
    void setEid(const QString& eid);
    void setPanels(QStringList panels);
private:
    QString m_eid;
    QStringList m_panels;
};
}
}
}

#endif // WORKSPACE_H
