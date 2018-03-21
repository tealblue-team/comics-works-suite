#ifndef WORKSPACE_BASE_H
#define WORKSPACE_BASE_H

#include <QObject>

namespace comics {
namespace works {
namespace entities {
class WorkspaceBase : public QObject
{
    Q_OBJECT
protected:
    explicit WorkspaceBase(QObject *parent = nullptr) {}
public:
    virtual QString eid() const = 0;
    virtual QStringList panels() const = 0;
    virtual void setEid(const QString& eid) = 0;
    virtual void setPanels(QStringList panels) = 0;
};
}
}
}

#endif // WORKSPACE_BASE_H
