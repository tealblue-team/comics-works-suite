#include <QString>
#include <QtTest>
#include "project.h"

using namespace comics::works::entities;

class ProjectTest : public QObject
{
    Q_OBJECT

public:
    ProjectTest();

private Q_SLOTS:
    void test_ctor();
    void test_eid();
};

ProjectTest::ProjectTest()
{
}

void ProjectTest::test_ctor()
{
    // WHEN
    QScopedPointer<Project> project(new Project("someId"));
    // THEN
    QVERIFY(project.data());
    QVERIFY(project->panels());
    QVERIFY(project->characters());
}

void ProjectTest::test_eid()
{
    // WHEN
    QScopedPointer<Project> project(new Project("someId"));
    // THEN
    QCOMPARE(project->eid(),QString("someId"));
}

QTEST_APPLESS_MAIN(ProjectTest)

#include "tst_project.moc"
