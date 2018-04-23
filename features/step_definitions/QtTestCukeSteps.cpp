#include <cstdlib>
#include <QTest>
#include <QSignalSpy>
#include <cucumber-cpp/autodetect.hpp>
#include "comics/works/entities/register.h"
#include "comics/works/entities/character/character.h"
#include "comics/works/entities/panel/panel.h"
#include "comics/works/entities/workspace/workspace.h"
#include "comics/works/usecases/usecases.h"

using cucumber::ScenarioScope;
using namespace comics::works;

/// Helper class to ensure that QApplication gets destroyed before main() returns
/// and that CalculatorWidget gets destroyed before QApplication gets destroyed.
struct MainCtx {
    MainCtx()
        : argc(0)
        , app(argc, nullptr)
    {
        uc.entities_reg = &entities;
    }
    int argc;
    QCoreApplication app;
    QVariantMap usecaseResult;
    usecases uc;
    entities::Register entities;
};

std::istream& operator>> (std::istream& in, QString& val) { std::string s; in >> s; val = s.c_str(); return in; }
std::ostream& operator<< (std::ostream& out, const QString& val) { out << val.toLatin1().data(); return out; }

CUKE_STEP_("^I try to create a workspace with name \"([a-zA-Z]+[0-9]*)\"$") {
    REGEX_PARAM(QString, workspaceId);
    ScenarioScope<MainCtx> ctx;
    QSignalSpy usecaseResult(&ctx->uc, &usecases::usecaseCompleted);
    ctx->uc.create_workspace(workspaceId);
    usecaseResult.wait(5);
    ctx->usecaseResult = usecaseResult.takeFirst().at(0).toMap();
}

CUKE_STEP_("^the workspace with name \"([a-zA-Z]+[0-9]*)\" is created$") {
    REGEX_PARAM(QString, workspaceId);
    ScenarioScope<MainCtx> ctx;
    QCOMPARE(ctx->entities.currentWorkspace->eid(), workspaceId);
}

CUKE_STEP_("^no pile with name \"([a-zA-Z]+[0-9]*)\" exists in the current workspace$") {
    REGEX_PARAM(QString, pileId);
    ScenarioScope<MainCtx> ctx;
    QVERIFY(! ctx->entities.currentWorkspace->piles().contains(pileId));
}

CUKE_STEP_("^no panel with name \"([a-zA-Z]+[0-9]*)\" exists in the current workspace$") {
    REGEX_PARAM(QString, panelId);
    ScenarioScope<MainCtx> ctx;
    bool panelExists = false;
    for (int i = 0; i < ctx->entities.currentWorkspace->panels()->size(); ++i) {
        if (ctx->entities.currentWorkspace->panels()->at(i)->eid() == panelId) {
            panelExists = true;
            break;
        }
    }
    QVERIFY(! panelExists);
}

CUKE_STEP_("^no workspace with name \"([a-zA-Z]+[0-9]*)\" exists$") {
    REGEX_PARAM(QString, workspaceId);
    ScenarioScope<MainCtx> ctx;
    bool workspaceExists = ctx->entities.currentWorkspace != nullptr;
    QVERIFY(! workspaceExists);
}

CUKE_STEP_("^a pile with name \"([a-zA-Z]+[0-9]*)\" exists in the current workspace$") {
    REGEX_PARAM(QString, pileId);
    ScenarioScope<MainCtx> ctx;
    QVERIFY(ctx->entities.currentWorkspace->piles().contains(pileId));
}

CUKE_STEP_("^a panel with name \"([a-zA-Z]+[0-9]*)\" exists in the current workspace$") {
    REGEX_PARAM(QString, panelId);
    ScenarioScope<MainCtx> ctx;
    bool panelExists = false;
    for (int i = 0; i < ctx->entities.currentWorkspace->panels()->size(); ++i) {
        if (ctx->entities.currentWorkspace->panels()->at(i)->eid() == panelId) {
            panelExists = true;
            break;
        }
    }
    QVERIFY(panelExists);
}

CUKE_STEP_("^I try to create a pile with name \"([a-zA-Z]+[0-9]*)\"$") {
    REGEX_PARAM(QString, pileId);
    ScenarioScope<MainCtx> ctx;
    ctx->usecaseResult = ctx->uc.create_pile(pileId, ctx->entities.currentWorkspace->eid());
}

CUKE_STEP_("^I can lookup the pile with name \"([a-zA-Z]+[0-9]*)\" in the current workspace$") {
    REGEX_PARAM(QString, pileId);
    ScenarioScope<MainCtx> ctx;
    QVERIFY(ctx->entities.currentWorkspace->piles().contains(pileId));
}

CUKE_STEP_("^the pile with name \"([a-zA-Z]+[0-9]*)\" is created$") {
    REGEX_PARAM(QString, pileId);
    ScenarioScope<MainCtx> ctx;
    QCOMPARE(ctx->usecaseResult.value("eid").toString(), pileId);
    QCOMPARE(ctx->usecaseResult.value("outcome").toString(), QString("PILE_CREATED"));
}

CUKE_STEP_("^the pile with name \"([a-zA-Z]+[0-9]*)\" is not created$") {
    REGEX_PARAM(QString, pileId);
    ScenarioScope<MainCtx> ctx;
    QCOMPARE(ctx->usecaseResult.value("eid").toString(), pileId);
    QCOMPARE(ctx->usecaseResult.value("outcome").toString(), QString("PILE_NOT_CREATED"));
}

CUKE_STEP_("^the panel with name \"([a-zA-Z]+[0-9]*)\" is not created$") {
    REGEX_PARAM(QString, panelId);
    ScenarioScope<MainCtx> ctx;
    QCOMPARE(ctx->usecaseResult.value("eid").toString(), panelId);
    QCOMPARE(ctx->usecaseResult.value("outcome").toString(), QString("PANEL_NOT_CREATED"));
}

CUKE_STEP_("^I am told that a pile with name \"([a-zA-Z]+[0-9]*)\" already exists$") {
    REGEX_PARAM(QString, pileId);
    ScenarioScope<MainCtx> ctx;
    QCOMPARE(ctx->usecaseResult.value("eid").toString(), pileId);
    QCOMPARE(ctx->usecaseResult.value("reason").toString(),QString("PILE_ALREADY_EXISTS"));
}

CUKE_STEP_("^I am told that a panel with name \"([a-zA-Z]+[0-9]*)\" already exists$") {
    REGEX_PARAM(QString, panelId);
    ScenarioScope<MainCtx> ctx;
    QCOMPARE(ctx->usecaseResult.value("eid").toString(), panelId);
    QCOMPARE(ctx->usecaseResult.value("reason").toString(),QString("PANEL_ALREADY_EXISTS"));
}

CUKE_STEP_("^I try to create a panel with name \"([a-zA-Z]+[0-9]*)\"$") {
    REGEX_PARAM(QString, panelId);
    ScenarioScope<MainCtx> ctx;
    QSignalSpy usecaseResult(&ctx->uc, &usecases::usecaseCompleted);
    ctx->uc.create_panel(panelId, ctx->entities.currentWorkspace->eid());
    usecaseResult.wait(5);
    ctx->usecaseResult = usecaseResult.takeFirst().at(0).toMap();
}

CUKE_STEP_("^I try to delete a panel with name \"([a-zA-Z]+[0-9]*)\"$") {
    REGEX_PARAM(QString, panelId);
    ScenarioScope<MainCtx> ctx;
    QSignalSpy usecaseResult(&ctx->uc, &usecases::usecaseCompleted);
    ctx->uc.delete_panel(panelId, ctx->entities.currentWorkspace->eid());
    usecaseResult.wait(5);
    ctx->usecaseResult = usecaseResult.takeFirst().at(0).toMap();
}

CUKE_STEP_("^the panel with name \"([a-zA-Z]+[0-9]*)\" is created$") {
    REGEX_PARAM(QString, panelId);
    ScenarioScope<MainCtx> ctx;
    QCOMPARE(ctx->usecaseResult.value("eid").toString(), panelId);
    QCOMPARE(ctx->usecaseResult.value("outcome").toString(), QString("PANEL_CREATED"));
}

CUKE_STEP_("^the panel with name \"([a-zA-Z]+[0-9]*)\" is deleted$") {
    REGEX_PARAM(QString, panelId);
    ScenarioScope<MainCtx> ctx;
    QCOMPARE(ctx->usecaseResult.value("eid").toString(), panelId);
    QCOMPARE(ctx->usecaseResult.value("outcome").toString(), QString("PANEL_DELETED"));
}

CUKE_STEP_("^I can lookup the panel with name \"([a-zA-Z]+[0-9]*)\" in the current workspace$") {
    REGEX_PARAM(QString, panelId);
    ScenarioScope<MainCtx> ctx;
    bool found = false;
    for (int i = 0; i < ctx->entities.currentWorkspace->panels()->size(); ++i) {
        if (ctx->entities.currentWorkspace->panels()->at(i)->eid() == panelId) {
            found = true;
            break;
        }
    }
    QVERIFY(found);
}

CUKE_STEP_("^I cannot lookup the panel with name \"([a-zA-Z]+[0-9]*)\" in the current workspace$") {
    REGEX_PARAM(QString, panelId);
    ScenarioScope<MainCtx> ctx;
    bool found = false;
    for (int i = 0; i < ctx->entities.currentWorkspace->panels()->size(); ++i) {
        if (ctx->entities.currentWorkspace->panels()->at(i)->eid() == panelId) {
            found = true;
            break;
        }
    }
    QVERIFY(! found);
}

CUKE_STEP_("^the width of panel \"([a-zA-Z]+[0-9]*)\" is greater than \"(\\d+)\"$") {
    REGEX_PARAM(QString, panelId);
    REGEX_PARAM(int, zeroWidth);
    ScenarioScope<MainCtx> ctx;
    int idx = -1;
    for (int i = 0; i < ctx->entities.currentWorkspace->panels()->size(); ++i) {
        if (ctx->entities.currentWorkspace->panels()->at(i)->eid() == panelId) {
            idx = i;
            break;
        }
    }
    if (idx > -1)
        QVERIFY(ctx->entities.currentWorkspace->panels()->at(idx)->width() > zeroWidth);
}

CUKE_STEP_("^the height of panel \"([a-zA-Z]+[0-9]*)\" is greater than \"(\\d+)\"$") {
    REGEX_PARAM(QString, panelId);
    REGEX_PARAM(int, zeroHeight);
    ScenarioScope<MainCtx> ctx;
    int idx = -1;
    for (int i = 0; i < ctx->entities.currentWorkspace->panels()->size(); ++i) {
        if (ctx->entities.currentWorkspace->panels()->at(i)->eid() == panelId) {
            idx = i;
            break;
        }
    }
    if (idx > -1)
        QVERIFY(ctx->entities.currentWorkspace->panels()->at(idx)->height() > zeroHeight);
}

CUKE_STEP_("^I try to describe panel \"([a-zA-Z]+[0-9]*)\" as \"(.+)\"$") {
    REGEX_PARAM(QString, panelId);
    REGEX_PARAM(QString, panelDescription);
    ScenarioScope<MainCtx> ctx;
    QSignalSpy usecaseResult(&ctx->uc, &usecases::usecaseCompleted);
    ctx->uc.describe_panel(panelId, panelDescription);
    usecaseResult.wait(5);
    ctx->usecaseResult = usecaseResult.takeFirst().at(0).toMap();
}

CUKE_STEP_("^a description is added to panel \"([a-zA-Z]+[0-9]*)\"$") {
    REGEX_PARAM(QString, panelId);
    ScenarioScope<MainCtx> ctx;
    QCOMPARE(ctx->usecaseResult.value("eid").toString(), panelId);
    QCOMPARE(ctx->usecaseResult.value("outcome").toString(), QString("PANEL_DESCRIBED"));
}

CUKE_STEP_("^the description for panel \"([a-zA-Z]+[0-9]*)\" reads \"(.+)\"$") {
    REGEX_PARAM(QString, panelId);
    REGEX_PARAM(QString, panelDescription);
    ScenarioScope<MainCtx> ctx;
    bool descriptionFound = false;
    for (int i = 0; i < ctx->entities.currentWorkspace->panels()->size(); ++i) {
        if ((ctx->entities.currentWorkspace->panels()->at(i)->eid() == panelId)
                && (ctx->entities.currentWorkspace->panels()->at(i)->description() == panelDescription)) {
            descriptionFound = true;
            break;
        }
    }
    QVERIFY(descriptionFound);
}

CUKE_STEP_("^no character with name \"([a-zA-Z0-9]+)\" exists in the current workspace$") {
    REGEX_PARAM(QString, characterName);
    ScenarioScope<MainCtx> ctx;
    bool characterExists = false;
    for (int i = 0; i < ctx->entities.currentWorkspace->characters()->size(); ++i) {
        if (ctx->entities.currentWorkspace->characters()->at(i)->name() == characterName) {
            characterExists = true;
            break;
        }
    }
    QVERIFY(! characterExists);
}

CUKE_STEP_("^I try to create a character with name \"([a-zA-Z0-9]+)\"$") {
    REGEX_PARAM(QString, characterName);
    ScenarioScope<MainCtx> ctx;
    QSignalSpy usecaseResult(&ctx->uc, &usecases::usecaseCompleted);
    ctx->uc.create_character(characterName, ctx->entities.currentWorkspace->eid());
    usecaseResult.wait(5);
    ctx->usecaseResult = usecaseResult.takeFirst().at(0).toMap();
}

CUKE_STEP_("^the character with name \"([a-zA-Z0-9]+)\" is created$") {
    REGEX_PARAM(QString, characterName);
    ScenarioScope<MainCtx> ctx;
    QCOMPARE(ctx->usecaseResult.value("name").toString(), characterName);
    QCOMPARE(ctx->usecaseResult.value("outcome").toString(), QString("CHARACTER_CREATED"));
}

CUKE_STEP_("^I can lookup the character with name \"([a-zA-Z0-9]+)\" in the current workspace$") {
    REGEX_PARAM(QString, characterName);
    ScenarioScope<MainCtx> ctx;
    bool found = false;
    for (int i = 0; i < ctx->entities.currentWorkspace->characters()->size(); ++i) {
        if (ctx->entities.currentWorkspace->characters()->at(i)->name() == characterName) {
            found = true;
            break;
        }
    }
    QVERIFY(found);
}

CUKE_STEP_("^I try to add a dialog saying \"(.+)\" for character \"([a-zA-Z0-9]+)\" to panel \"([a-zA-Z]+[0-9]*)\"$") {
    REGEX_PARAM(QString, dialogContent);
    REGEX_PARAM(QString, characterName);
    REGEX_PARAM(QString, panelName);
    ScenarioScope<MainCtx> ctx;
    QSignalSpy usecaseResult(&ctx->uc, &usecases::usecaseCompleted);
    ctx->uc.add_dialog_to_panel(dialogContent, characterName, panelName);
    usecaseResult.wait(5);
    ctx->usecaseResult = usecaseResult.takeFirst().at(0).toMap();
}

CUKE_STEP_("^a dialog is added to panel \"([a-zA-Z]+[0-9]*)\"$") {
    REGEX_PARAM(QString, panelName);
    ScenarioScope<MainCtx> ctx;
    bool dialogFound = false;
    for (int i = 0; i < ctx->entities.currentWorkspace->panels()->size(); ++i) {
        if ((ctx->entities.currentWorkspace->panels()->at(i)->eid() == panelName)
                && (ctx->entities.currentWorkspace->panels()->at(i)->dialogs().length() > 0)) {
            dialogFound = true;
            break;
        }
    }
    QVERIFY(dialogFound);
}

CUKE_STEP_("^the first dialog for panel \"([a-zA-Z]+[0-9]*)\" belongs to character \"([a-zA-Z0-9]+)\"$") {
    REGEX_PARAM(QString, panelName);
    REGEX_PARAM(QString, characterName);
    ScenarioScope<MainCtx> ctx;
    bool dialogFound = false;
    for (int i = 0; i < ctx->entities.currentWorkspace->panels()->size(); ++i) {
        if ((ctx->entities.currentWorkspace->panels()->at(i)->eid() == panelName)
                && (ctx->entities.currentWorkspace->panels()->at(i)->dialogs().at(0).value("characterName") == characterName)) {
            dialogFound = true;
            break;
        }
    }
    QVERIFY(dialogFound);
}


CUKE_STEP_("^the first dialog for panel \"([a-zA-Z]+[0-9]*)\" reads \"(.+)\"$") {
    REGEX_PARAM(QString, panelName);
    REGEX_PARAM(QString, dialogContent);
    ScenarioScope<MainCtx> ctx;
    bool dialogFound = false;
    for (int i = 0; i < ctx->entities.currentWorkspace->panels()->size(); ++i) {
        if ((ctx->entities.currentWorkspace->panels()->at(i)->eid() == panelName)
                && (ctx->entities.currentWorkspace->panels()->at(i)->dialogs().at(0).value("dialogContent") == dialogContent)) {
            dialogFound = true;
            break;
        }
    }
    QVERIFY(dialogFound);
}

