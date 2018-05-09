#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "project_json.h"
#include "comics/works/usecases/usecases.h"

using namespace comics::works::adapters;

ProjectJson::ProjectJson(QObject *parent) : QObject(parent)
{
}

void ProjectJson::loadFrom(const QJsonDocument& projectJsonDoc, comics::works::usecases* uc)
{
    auto jsonObject = projectJsonDoc.object();
    auto charactersJson = jsonObject.value("characters").toArray();
    auto panelsJson = jsonObject.value("panels").toArray();
    connect(uc, &usecases::characterCreated, [uc, charactersJson, panelsJson](QVariant value) {
        auto characters = value.toMap().value("characters").toList();
        if (characters.size() == charactersJson.size()) {
            for (int i=0;i<panelsJson.size();++i) {
                auto panelEid = panelsJson.at(i).toObject().value("eid").toString();
                uc->create_panel(panelEid, uc->entities_reg->currentWorkspace->eid());
            }
        }
    });
    connect(uc, &usecases::panelCreated, [=](QVariant value) {
        auto panels = value.toMap().value("panels").toList();
        if (panels.size() == panelsJson.size()) {
            for (int i=0;i<panels.size();++i) {
                auto panelEid = panels.at(i).toMap().value("eid").toString();
                auto panelDescription = panelsJson.at(i).toObject().value("description").toString();
                m_descriptionsCount += 1;
                uc->describe_panel(panelEid, panelDescription);
            }
        }
    });
    connect(uc, &usecases::panelDescribed, [=](QVariant value) {
        auto panels = value.toMap().value("panels").toList();
        if (panels.size() == m_descriptionsCount) {
            for (int i=0;i<panels.size();++i) {
                auto panelEid = panels.at(i).toMap().value("eid").toString();
                auto panelCharacters = panelsJson.at(i).toObject().value("characters").toArray();
                for (int j=0;j<panelCharacters.size();++j) {
                    m_panelCharactersCount += 1;
                    uc->add_character_to_panel(panelCharacters.at(j).toString(), panelEid);
                }
            }
        }
    });
    connect(uc, &usecases::characterAddedToPanel, [=](QVariant value) {
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
                    uc->add_dialog_to_panel(
                                dialogJson.value("dialogContent_en_US").toString(),
                                dialogJson.value("characterName").toString(),
                                panelsJson.at(i).toObject().value("eid").toString()
                                );
                }
            }
        }
    });
    connect(uc, &usecases::dialogAddedToPanel, [=](QVariant value) {
        int dialogsCount = 0;
        for (int i=0;i<panelsJson.size();++i) {
            auto panelDialogs = panelsJson.at(i).toObject().value("dialogs").toArray();
            for (int j=0;j<panelDialogs.size();++j) {
                dialogsCount += 1;
            }
        }
        if (dialogsCount == m_dialogsCount) {
            emit completed(0);
        }
    });
    for (int i=0;i<charactersJson.size();++i) {
        auto characterName = charactersJson.at(i).toObject().value("name").toString();
        uc->create_character(characterName, uc->entities_reg->currentWorkspace->eid());
    }

}
