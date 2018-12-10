#include <QDebug>

#include "panel.h"
#include <QVariantMap>
#include <QVector>

using namespace comics::works::entities;

Panel::Panel(const QString& eid, QObject *parent)
    : PanelBase(parent),
      m_characters(new QVector<CharacterBase*>)
{
    setEid(eid);
}

const QString& Panel::description() const {
    return m_description;
}

QVariantList Panel::dialogs() const
{
    return m_dialogs;
}

const QString& Panel::eid() const {
    return m_eid;
}

const QString& Panel::name() const {
    return m_name;
}

int Panel::width() const {
    return m_width;
}

int Panel::height() const {
    return m_height;
}

QVector<CharacterBase *> *Panel::characters() const
{
    return m_characters;
}

void Panel::addCharacter(CharacterBase* character) {
    if (! m_characters->contains(character))
        m_characters->append(character);
}

void Panel::addDialog(const QString &dialogId, const QString &dialogContent, const QString &characterName)
{
    QVariantMap dialog({
                           {"dialogId", dialogId},
                           {"dialogContent_en_US", dialogContent},
                           {"characterName", characterName},
                       });
    m_dialogs.append(QVariant(dialog));
}

void Panel::removeDialog(const QString &dialogId, const QString &dialogContent, const QString &characterName)
{
    QVariantMap dialog({
                           {"dialogId", dialogId},
                           {"dialogContent_en_US", dialogContent},
                           {"characterName", characterName},
                       });
    qDebug() << m_dialogs;
    m_dialogs.removeAt(m_dialogs.indexOf(QVariant(dialog)));
    qDebug() << m_dialogs;
}

void Panel::setDescription(const QString& description)
{
    if (m_description != description)
        m_description = description;
}

void Panel::setEid(const QString& eid) {
    if (m_eid != eid && eid != "")
        m_eid = eid;
}

void Panel::setName(const QString& name) {
    if (m_name != name)
        m_name = name;
}

void Panel::setWidth(int width) {
    if (m_width != width && width > 0)
        m_width = width;
}

void Panel::setHeight(int height) {
    if (m_height != height && height > 0)
        m_height = height;
}
