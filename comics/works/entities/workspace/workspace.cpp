#include "workspace.h"

using namespace comics::works::entities;

Workspace::Workspace(const QString& eid, QObject *parent)
    : WorkspaceBase(parent)
{
    setEid(eid);
}

QString Workspace::eid() const {
    return m_eid;
}

QStringList Workspace::panels() const {
    return m_panels;
}

void Workspace::setEid(const QString& eid) {
    if (m_eid != eid && eid != "")
        m_eid = eid;
}

void Workspace::setPanels(QStringList panels) {
    m_panels = panels;
}
