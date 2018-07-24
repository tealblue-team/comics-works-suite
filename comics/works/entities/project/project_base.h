#ifndef PROJECT_BASE_H
#define PROJECT_BASE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QVariantList>

namespace comics {
namespace works {
namespace entities {
class CharacterBase;
class PanelBase;
class ProjectBase : public QObject
{
    Q_OBJECT
protected:
    explicit ProjectBase(QObject *parent = nullptr) {}
public:
    virtual QVector<CharacterBase*>* characters() const = 0;
    virtual const QString& eid() const = 0;
    virtual const QString& name() const = 0;
    virtual QVector<PanelBase*>* panels() const = 0;
    virtual QVariantList piles() const = 0;

    virtual void addCharacter(CharacterBase*) = 0;
    virtual void addPanel(PanelBase*) = 0;
    virtual void setEid(const QString&) = 0;
    virtual void setName(const QString&) = 0;
    virtual void setPiles(QVariantList) = 0;
};
}
}
}

#endif // PROJECT_BASE_H
