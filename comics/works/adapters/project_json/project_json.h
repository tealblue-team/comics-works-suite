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
    explicit ProjectJson(QObject *parent = nullptr);
    void loadFrom(const QJsonDocument&, usecases*);
signals:
    void completed(int success);
private:
    int m_descriptionsCount = 0;
    int m_dialogsCount = 0;
    int m_panelCharactersCount = 0;
};
}
}
}

#endif // PROJECT_JSON_H
