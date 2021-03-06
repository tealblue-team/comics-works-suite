#ifndef USECASES_H
#define USECASES_H
#include <QVariantMap>
class QString;
#include "comics/works/entities/register.h"
#include "comics/works/entities/panel/panel_base.h"

namespace comics {
namespace works {
class usecases : public QObject {
    Q_OBJECT
public:
    explicit usecases(QObject* parent = nullptr);
    Q_INVOKABLE void add_character_to_panel(const QString& characterName, const QString& panelId);
    Q_INVOKABLE void add_dialog_to_panel(const QString& dialogId, const QString& dialogContent, const QString& characterName, const QString& panelId);
    Q_INVOKABLE void create_character(const QString& characterName, const QString& projectName);
    Q_INVOKABLE void create_panel(const QString& panelId, const QString& projectName);
    Q_INVOKABLE QVariantMap create_pile(const QString& pileName, const QString& projectName);
    Q_INVOKABLE void create_project(const QString& projectName);
    Q_INVOKABLE void delete_character(const QString& characterName, const QString& projectName);
    Q_INVOKABLE void delete_dialog_from_panel(const QString& dialogId, const QString& panelId, const QString& projectName);
    Q_INVOKABLE void delete_panel(const QString& panelId, const QString& projectName);
    Q_INVOKABLE void delete_project(const QString& projectName);
    Q_INVOKABLE void describe_panel(const QString& panelId, const QString& panelDescription);
    Q_INVOKABLE void name_panel(const QString& panelId, const QString& panelName);
    Q_INVOKABLE void name_project(const QString& projectId, const QString& projectName);

    QVariantList _getCharactersList(QVector<entities::CharacterBase*>*) const;
    QVariantList _getPanelsList(QVector<entities::PanelBase*>*) const;
    entities::Register* entities_reg = nullptr;
signals:
    void usecaseCompleted(QVariantMap value);

    void characterAddedToPanel(QVariantMap value);
    void characterCreated(QVariantMap value);
    void characterDeleted(QVariantMap value);
    void characterNotCreated(QVariantMap value);
    void dialogAddedToPanel(QVariantMap value);
    void dialogDeletedFromPanel(QVariantMap value);
    void panelCreated(QVariantMap value);
    void panelDeleted(QVariantMap value);
    void panelDescribed(QVariantMap value);
    void panelNamed(QVariantMap value);
    void panelNotCreated(QVariantMap value);
    void projectCreated(QVariantMap value);
    void projectNamed(QVariantMap value);
    void projectDeleted(QVariantMap value);
};
}
}

#endif // USECASES_H
