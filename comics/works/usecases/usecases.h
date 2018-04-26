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
    Q_INVOKABLE void add_character_to_panel(const QString& characterName, const QString& panelName);
    Q_INVOKABLE void add_dialog_to_panel(const QString& dialogContent, const QString& characterName, const QString& panelName);
    Q_INVOKABLE void create_character(const QString& characterName, const QString& workspaceName);
    Q_INVOKABLE void create_panel(const QString& panelName, const QString& workspaceName);
    Q_INVOKABLE QVariantMap create_pile(const QString& pileName, const QString& workspaceName);
    Q_INVOKABLE void create_workspace(const QString& workspaceName);
    Q_INVOKABLE void delete_panel(const QString& panelName, const QString& workspaceName);
    Q_INVOKABLE void describe_panel(const QString& panelName, const QString& panelDescription);

    entities::Register* entities_reg = nullptr;
signals:
    void usecaseCompleted(QVariantMap value);

    void characterAddedToPanel(QVariantMap value);
    void characterCreated(QVariantMap value);
    void characterNotCreated(QVariantMap value);
    void dialogAddedToPanel(QVariantMap value);
    void panelCreated(QVariantMap value);
    void panelDeleted(QVariantMap value);
    void panelDescribed(QVariantMap value);
    void panelNotCreated(QVariantMap value);
    void workspaceCreated(QVariantMap value);
private:
    QVariantList _getCharactersList(QVector<entities::CharacterBase*>*) const;
    QVariantList _getPanelsList(QVector<entities::PanelBase*>*) const;
};
}
}

#endif // USECASES_H
