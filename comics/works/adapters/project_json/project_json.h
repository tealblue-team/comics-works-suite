#ifndef PROJECT_JSON_H
#define PROJECT_JSON_H

#include <QObject>
#include <QJsonDocument>
#include <QUrl>

namespace comics {
namespace works {
class usecases;
class Utils;
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
    explicit ProjectJson(QObject *parent = nullptr);
    void setUsecases(usecases*);
    void setUtils(Utils*);
    Q_INVOKABLE void loadFromJsonDoc(const QByteArray&);
    Q_INVOKABLE void saveToJsonDoc();
    Q_INVOKABLE QByteArray readJsonFromFile(const QString&);
    Q_INVOKABLE QString writeJsonToFile(const QByteArray& json, const QString& filePath);
signals:
    void loaded(int success);
    void saved(QByteArray jsonDoc);
private:
    usecases* m_uc = nullptr;
    Utils* m_utils = nullptr;
    int m_descriptionsCount = 0;
    int m_dialogsCount = 0;
    int m_namesCount = 0;
    int m_panelCharactersCount = 0;
    QMetaObject::Connection m_addCharactersToPanels;
    QMetaObject::Connection m_addDialogsToPanels;
    QMetaObject::Connection m_createPanels;
    QMetaObject::Connection m_describePanels;
    QMetaObject::Connection m_namePanels;
};
}
}
}

#endif // PROJECT_JSON_H
