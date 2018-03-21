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
    void test_create();
};

WorkspaceTest::WorkspaceTest()
{
}

void WorkspaceTest::test_create()
{
    // WHEN
    QScopedPointer<Workspace> workspace (new Workspace("someId"));
    // THEN
    QCOMPARE(workspace->eid(),QString("someId"));
}

QTEST_APPLESS_MAIN(WorkspaceTest)

#include "tst_workspace.moc"
