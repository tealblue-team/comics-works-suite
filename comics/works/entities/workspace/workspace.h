#ifndef WORKSPACE_H
#define WORKSPACE_H
#include "workspace_base.h"

namespace comics {
namespace works {
namespace entities {
class Workspace : public WorkspaceBase
{
    Q_OBJECT
    Q_PROPERTY(QString eid READ eid NOTIFY eidChanged)
public:
    explicit Workspace(const QString& eid, QObject *parent = nullptr);

    QVector<CharacterBase*>* characters() const;
    const QString& eid() const;
    QVariantList piles() const;
    QVector<PanelBase*>* panels() const;

    void addPanel(PanelBase*);
    void addCharacter(CharacterBase*);
    void setEid(const QString&);
    void setPiles(QVariantList);
signals:
    void eidChanged();
private:
    QString m_eid;
    QVector<CharacterBase*>* m_characters;
    QVector<PanelBase*>* m_panels;
    QVariantList m_piles;
};
}
}
}

#endif // WORKSPACE_H
