#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QFile>
#include "project_json.h"
#include "comics/works/usecases/usecases.h"

using namespace comics::works::adapters;

ProjectJson::ProjectJson(QObject *parent) : QObject(parent)
{
}

void ProjectJson::setUsecases(usecases* uc)
{
    m_uc = uc;
}

void ProjectJson::loadFromJsonDoc(const QByteArray& projectJson)
{
    auto projectJsonDoc = QJsonDocument::fromJson(projectJson);
    auto jsonObject = projectJsonDoc.object();
    auto charactersJson = jsonObject.value("characters").toArray();
    auto panelsJson = jsonObject.value("panels").toArray();

    m_createPanels = connect(m_uc, &usecases::characterCreated, [=](QVariant value) {
        auto characters = value.toMap().value("characters").toList();
        if (characters.size() == charactersJson.size()) {
            for (int i=0;i<panelsJson.size();++i) {
                auto panelEid = panelsJson.at(i).toObject().value("eid").toString();
                m_uc->create_panel(panelEid, m_uc->entities_reg->currentWorkspace->eid());
            }
        }
    });
    m_describePanels = connect(m_uc, &usecases::panelCreated, [=](QVariant value) {
        auto panels = value.toMap().value("panels").toList();
        if (panels.size() == panelsJson.size()) {
            for (int i=0;i<panels.size();++i) {
                auto panelEid = panels.at(i).toMap().value("eid").toString();
                auto panelDescription = panelsJson.at(i).toObject().value("description").toString();
                m_descriptionsCount += 1;
                m_uc->describe_panel(panelEid, panelDescription);
            }
        }
    });
    m_addCharactersToPanels = connect(m_uc, &usecases::panelDescribed, [=](QVariant value) {
        auto panels = value.toMap().value("panels").toList();
        if (panels.size() == m_descriptionsCount) {
            for (int i=0;i<panels.size();++i) {
                auto panelEid = panels.at(i).toMap().value("eid").toString();
                auto panelCharacters = panelsJson.at(i).toObject().value("characters").toArray();
                for (int j=0;j<panelCharacters.size();++j) {
                    m_panelCharactersCount += 1;
                    m_uc->add_character_to_panel(panelCharacters.at(j).toString(), panelEid);
                }
            }
        }
    });
    m_addDialogsToPanels = connect(m_uc, &usecases::characterAddedToPanel, [=](QVariant value) {
        int charactersCount = 0;
        for (int i=0;i<panelsJson.size();++i) {
            auto panelCharacters = panelsJson.at(i).toObject().value("characters").toArray();
            for (int j=0;j<panelCharacters.size();++j) {
                charactersCount += 1;
            }
        }
        if (charactersCount == m_panelCharactersCount) {
            for (int i=0;i<panelsJson.size();++i) {
                auto panelDialogsJson = panelsJson.at(i).toObject().value("dialogs").toArray();
                for (int j=0;j<panelDialogsJson.size();++j) {
                    auto dialogJson = panelDialogsJson.at(j).toObject();
                    m_dialogsCount += 1;
                    m_uc->add_dialog_to_panel(
                                dialogJson.value("dialogContent_en_US").toString(),
                                dialogJson.value("characterName").toString(),
                                panelsJson.at(i).toObject().value("eid").toString()
                                );
                }
            }
        }
    });
    connect(m_uc, &usecases::dialogAddedToPanel, [=](QVariant value) {
        int dialogsCount = 0;
        for (int i=0;i<panelsJson.size();++i) {
            auto panelDialogs = panelsJson.at(i).toObject().value("dialogs").toArray();
            for (int j=0;j<panelDialogs.size();++j) {
                dialogsCount += 1;
            }
        }
        if (dialogsCount == m_dialogsCount) {
            m_descriptionsCount = 0;
            m_dialogsCount = 0;
            m_panelCharactersCount = 0;
            m_uc->disconnect(m_createPanels);
            m_uc->disconnect(m_describePanels);
            m_uc->disconnect(m_addCharactersToPanels);
            m_uc->disconnect(m_addDialogsToPanels);
            emit loaded(0);
        }
    });
    for (int i=0;i<charactersJson.size();++i) {
        auto characterName = charactersJson.at(i).toObject().value("name").toString();
        m_uc->create_character(characterName, m_uc->entities_reg->currentWorkspace->eid());
    }
}

void ProjectJson::saveToJsonDoc()
{
    auto projectJson = QJsonObject();
    projectJson["panels"] = QJsonArray::fromVariantList(m_uc->_getPanelsList(m_uc->entities_reg->currentWorkspace->panels()));
    projectJson["characters"] = QJsonArray::fromVariantList(m_uc->_getCharactersList(m_uc->entities_reg->currentWorkspace->characters()));
    auto projectJsonDoc = QJsonDocument(projectJson);
    emit saved(projectJsonDoc.toJson(QJsonDocument::Indented));
}


QByteArray ProjectJson::readJsonFromFile(const QString& filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QByteArray fileContent = file.readAll();
    file.close();
    return fileContent;
}

int ProjectJson::writeJsonToFile(const QByteArray& json, const QString& filePath)
{
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    file.write(json);
    return 0;
}