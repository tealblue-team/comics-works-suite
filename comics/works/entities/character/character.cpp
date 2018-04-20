#include "character.h"

using namespace comics::works::entities;

Character::Character(const QString& name, QObject* parent) : CharacterBase(parent)
{
    setName(name);
}

QString Character::name() const
{
    return m_name;
}

void Character::setName(const QString& name)
{
    if (! name.isEmpty()) {
        m_name = name;
        emit nameChanged(m_name);
    }
}
