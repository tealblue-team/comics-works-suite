#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include "character_base.h"

namespace comics {
namespace works {
namespace entities {
class Character : public CharacterBase
{
    Q_OBJECT
public:
    explicit Character(const QString& name, QObject* parent);

    QString name() const;

    void setName(const QString&);
signals:
    void nameChanged(const QString&);
private:
    QString m_name;
};
}
}
}

#endif // CHARACTER_H
