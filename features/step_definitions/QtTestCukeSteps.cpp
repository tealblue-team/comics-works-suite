#include <cstdlib>
#include <QTest>
#include <cucumber-cpp/autodetect.hpp>
#include "comics/works/entities/workspace/workspace.h"
#include "comics/works/usecases/usecases.h"

using cucumber::ScenarioScope;
using namespace comics::works;

/// Helper class to ensure that QApplication gets destroyed before main() returns
/// and that CalculatorWidget gets destroyed before QApplication gets destroyed.
struct MainCtx {
    MainCtx()
        : argc(0)
        , app(argc, NULL)
    {}

    int argc;
    bool usecaseSuccess;
    QCoreApplication app;
    QVariantMap usecaseResult;
    entities::Workspace* workspace = new entities::Workspace("workspace1",&app);
};

std::istream& operator>> (std::istream& in, QString& val) { std::string s; in >> s; val = s.c_str(); return in; }
std::ostream& operator<< (std::ostream& out, const QString& val) { out << val.toLatin1().data(); return out; }

CUKE_STEP_("^the current workspace exists$") {
    ScenarioScope<MainCtx> ctx;
    QCOMPARE(ctx->workspace->eid(), QString("workspace1"));
}

CUKE_STEP_("^no pile with name \"([a-zA-Z]+[0-9]*)\" exists in the current workspace$") {
    REGEX_PARAM(QString, pileId);
    ScenarioScope<MainCtx> ctx;
    QVERIFY(! ctx->workspace->panels().contains(pileId));
}

CUKE_STEP_("^a pile with name \"([a-zA-Z]+[0-9]*)\" exists in the current workspace$") {
    REGEX_PARAM(QString, pileId);
    ScenarioScope<MainCtx> ctx;
    ctx->usecaseResult = usecases::create_pile_with_name(pileId, ctx->workspace);
    QVERIFY(ctx->workspace->panels().contains(pileId));
}

CUKE_STEP_("^I create a pile with name \"([a-zA-Z]+[0-9]*)\"$") {
    REGEX_PARAM(QString, pileId);
    ScenarioScope<MainCtx> ctx;
    ctx->usecaseResult = usecases::create_pile_with_name(pileId, ctx->workspace);
}

CUKE_STEP_("^I can lookup \"([a-zA-Z]+[0-9]*)\" in the current workspace$") {
    REGEX_PARAM(QString, pileId);
    ScenarioScope<MainCtx> ctx;
    QVERIFY(ctx->workspace->panels().contains(pileId));
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

CUKE_STEP_("^I am told that a pile with name \"([a-zA-Z]+[0-9]*)\" already exists$") {
    REGEX_PARAM(QString, pileId);
    ScenarioScope<MainCtx> ctx;
    QCOMPARE(ctx->usecaseResult.value("eid").toString(), pileId);
    QCOMPARE(ctx->usecaseResult.value("reason").toString(),QString("PILE_ALREADY_EXISTS"));
}



