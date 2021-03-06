#ifndef PANEL_BASE_H
#define PANEL_BASE_H

#include <QObject>

namespace comics {
namespace works {
namespace entities {
class CharacterBase;
class PanelBase : public QObject
{
    Q_OBJECT
protected:
    explicit PanelBase(QObject* parent = nullptr) : QObject(parent) {}
public:
    virtual QVector<CharacterBase*>* characters() const = 0;
    virtual const QString& description() const = 0;
    virtual QVariantList dialogs() const = 0;
    virtual const QString& eid() const = 0;
    virtual const QString& name() const = 0;
    virtual int width() const = 0;
    virtual int height() const = 0;

    virtual void addCharacter(CharacterBase*) = 0;
    virtual void addDialog(const QString& dialogId, const QString& dialogContent, const QString& characterName) = 0;
    virtual void removeDialog(const QString& dialogId) = 0;
    virtual void setEid(const QString&) = 0;
    virtual void setDescription(const QString&) = 0;
    virtual void setName(const QString&) = 0;
    virtual void setWidth(int) = 0;
    virtual void setHeight(int) = 0;
};
}
}
}

#endif // PANEL_BASE_H
