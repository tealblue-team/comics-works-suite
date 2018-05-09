#ifndef PROJECT_JSON_H
#define PROJECT_JSON_H

#include <QObject>
#include <QJsonDocument>

namespace comics {
namespace works {
class usecases;
namespace adapters {
class ProjectJson : public QObject
{
    Q_OBJECT
public:
    explicit ProjectJson(usecases* uc, QObject *parent = nullptr);
    Q_INVOKABLE void loadFrom(const QByteArray&);
signals:
    void completed(int success);
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
