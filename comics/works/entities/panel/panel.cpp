#include "panel.h"
#include <QVariantMap>

using namespace comics::works::entities;

Panel::Panel(const QString& eid, QObject *parent)
    : PanelBase(parent)
{
    setEid(eid);
}

const QString& Panel::description() const {
    return m_description;
}

QList<QVariantMap> Panel::dialogs() const
{
    return m_dialogs;
}

const QString& Panel::eid() const {
    return m_eid;
}

int Panel::width() const {
    return m_width;
}

int Panel::height() const {
    return m_height;
}

void Panel::addDialog(const QString &dialogContent, const QString &characterName)
{
    QList<QVariantMap> dialogs = m_dialogs;
    QVariantMap dialog({
        {"dialogContent", dialogContent},
        {"characterName", characterName},
    });
    dialogs.append(dialog);
    m_dialogs = dialogs;
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

void Panel::setWidth(int width) {
    if (m_width != width && width > 0)
        m_width = width;
}

void Panel::setHeight(int height) {
    if (m_height != height && height > 0)
        m_height = height;
}
