#include "workspace.h"

using namespace comics::works::entities;

Workspace::Workspace(const QString& eid, QObject *parent)
    : WorkspaceBase(parent)
{
    setEid(eid);
}

void Workspace::addPanel(PanelBase* panel) {
    if (! m_panels.contains(panel))
        m_panels.append(panel);
}

const QString& Workspace::eid() const {
    return m_eid;
}

QVector<PanelBase*> Workspace::panels() const {
    return m_panels;
}

QVariantList Workspace::piles() const {
    return m_piles;
}

void Workspace::setEid(const QString& eid) {
    if (m_eid != eid && eid != "")
        m_eid = eid;
}

void Workspace::setPiles(QVariantList piles) {
    m_piles = piles;
}
