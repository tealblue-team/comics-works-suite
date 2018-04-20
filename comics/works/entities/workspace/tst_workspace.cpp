#include <QString>
#include <QtTest>
#include "workspace.h"

using namespace comics::works::entities;

class WorkspaceTest : public QObject
{
    Q_OBJECT

public:
    WorkspaceTest();

private Q_SLOTS:
    void test_ctor();
    void test_eid();
};

WorkspaceTest::WorkspaceTest()
{
}

void WorkspaceTest::test_ctor()
{
    // WHEN
    QScopedPointer<Workspace> workspace(new Workspace("someId"));
    // THEN
    QVERIFY(workspace.data());
    QVERIFY(workspace->panels());
    QVERIFY(workspace->characters());
}

void WorkspaceTest::test_eid()
{
    // WHEN
    QScopedPointer<Workspace> workspace(new Workspace("someId"));
    // THEN
    QCOMPARE(workspace->eid(),QString("someId"));
}

QTEST_APPLESS_MAIN(WorkspaceTest)

#include "tst_workspace.moc"
