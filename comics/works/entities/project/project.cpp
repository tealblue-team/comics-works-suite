#include "project.h"

using namespace comics::works::entities;

Project::Project(const QString& eid, QObject *parent)
    : ProjectBase(parent),
      m_characters(new QVector<CharacterBase*>),
      m_panels(new QVector<PanelBase*>)
{
    setEid(eid);
}

QVector<CharacterBase *> *Project::characters() const
{
    return m_characters;
}

void Project::addCharacter(CharacterBase* character) {
    if (! m_characters->contains(character))
        m_characters->append(character);
}

void Project::addPanel(PanelBase* panel) {
    if (! m_panels->contains(panel))
        m_panels->append(panel);
}

const QString& Project::eid() const {
    return m_eid;
}

QVector<PanelBase*>* Project::panels() const {
    return m_panels;
}

QVariantList Project::piles() const {
    return m_piles;
}

void Project::setEid(const QString& eid) {
    if (m_eid != eid && eid != "") {
        m_eid = eid;
        emit eidChanged();
    }
}

void Project::setPiles(QVariantList piles) {
    m_piles = piles;
}
