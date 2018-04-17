#include <cstdlib>
#include <QTest>
#include <QSignalSpy>
#include <cucumber-cpp/autodetect.hpp>
#include "comics/works/entities/register.h"
#include "comics/works/entities/workspace/workspace.h"
#include "comics/works/entities/panel/panel.h"
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
    bool usecaseSuccess;
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


