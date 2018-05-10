#ifndef PROJECT_JSON_H
#define PROJECT_JSON_H

#include <QObject>
#include <QJsonDocument>

namespace comics {
namespace works {
class usecases;
namespace entities {
class Register;
class PanelBase;
class CharacterBase;
}
namespace adapters {
class ProjectJson : public QObject
{
    Q_OBJECT
public:
    explicit ProjectJson(usecases* uc, QObject *parent = nullptr);
    Q_INVOKABLE void loadFromJsonDoc(const QByteArray&);
    Q_INVOKABLE void saveToJsonDoc(const entities::Register &);
signals:
    void loaded(int success);
    void saved(QByteArray jsonDoc);
private:
    usecases* m_uc = nullptr;
    int m_descriptionsCount = 0;
    int m_dialogsCount = 0;
    int m_panelCharactersCount = 0;
    QMetaObject::Connection m_createPanels;
    QMetaObject::Connection m_describePanels;
    QMetaObject::Connection m_addCharactersToPanels;
    QMetaObject::Connection m_addDialogsToPanels;
};
}
}
}

#endif // PROJECT_JSON_H
