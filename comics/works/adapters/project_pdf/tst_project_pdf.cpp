#include <QString>
#include <QtTest>

class ProjectPdfTest : public QObject
{
    Q_OBJECT

public:
    ProjectPdfTest();

private Q_SLOTS:
    void test_saveToPdf();
};

ProjectPdfTest::ProjectPdfTest()
{
}

void ProjectPdfTest::test_saveToPdf()
{
    QFAIL("not implemented");
}

QTEST_APPLESS_MAIN(ProjectPdfTest)

#include "tst_project_pdf.moc"
