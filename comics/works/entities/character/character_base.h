#ifndef CHARACTER_BASE_H
#define CHARACTER_BASE_H
#include <QObject>

namespace comics {
namespace works {
namespace entities {
class CharacterBase : public QObject
{
    Q_OBJECT
protected:
    explicit CharacterBase(QObject* parent) : QObject(parent) {}
public:
    virtual QString name() const = 0;

    virtual void setName(const QString&) = 0;
};
}
}
}

#endif // CHARACTER_BASE_H
