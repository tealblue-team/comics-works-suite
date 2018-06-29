#ifndef PROJECT_H
#define PROJECT_H
#include "project_base.h"

namespace comics {
namespace works {
namespace entities {
class Project : public ProjectBase
{
    Q_OBJECT
    Q_PROPERTY(QString eid READ eid NOTIFY eidChanged)
public:
    explicit Project(const QString& eid, QObject *parent = nullptr);

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

#endif // PROJECT_H
