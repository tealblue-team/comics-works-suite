#ifndef WORKSPACE_BASE_H
#define WORKSPACE_BASE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QVariantList>

namespace comics {
namespace works {
namespace entities {
class PanelBase;
class WorkspaceBase : public QObject
{
    Q_OBJECT
protected:
    explicit WorkspaceBase(QObject *parent = nullptr) {}
public:
    virtual const QString& eid() const = 0;
    virtual QVariantList piles() const = 0;
    virtual QVector<PanelBase*>* panels() const = 0;

    virtual void addPanel(PanelBase* panel) = 0;
    virtual void setEid(const QString& eid) = 0;
    virtual void setPiles(QVariantList piles) = 0;
};
}
}
}

#endif // WORKSPACE_BASE_H
