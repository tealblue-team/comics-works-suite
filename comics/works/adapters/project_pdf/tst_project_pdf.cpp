#include <QString>
#include <QtTest>
#include <QFileInfo>
#include "project_pdf.h"
#include "comics/works/adapters/project_json/project_json.h"
#include "comics/works/usecases/usecases.h"
#include "comics/works/entities/register.h"

using namespace comics::works;

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
    // Given
    // load json into memory
    // Given
    entities::Register entities_register;
    QScopedPointer<usecases> uc(new usecases());
    uc->entities_reg = &entities_register;
    // Given
    QByteArray projectJsonDoc(
                "{\n"
                "    \"characters\":[{\"name\":\"Ayran\"},{\"name\":\"Birun\"},{\"name\":\"Dilgun\"},{\"name\":\"Barsun\"}],\n"
                "    \"panels\":[\n"
                "        {\"characters\":[\"Ayran\",\"Birun\"],\"description\":\"first scene\",\"dialogs\":[{\"characterName\":\"Ayran\",\"dialogContent_en_US\":\"Hello\"},{\"characterName\":\"Birun\",\"dialogContent_en_US\":\"Hi\"}],\"eid\":\"panelABC\",\"name\":\"HL-I-1\"},\n"
                "        {\"characters\":[\"Barsun\",\"Dilgun\"],\"description\":\"second scene\",\"dialogs\":[{\"characterName\":\"Dilgun\",\"dialogContent_en_US\":\"Hey\"},{\"characterName\":\"Barsun\",\"dialogContent_en_US\":\"Hey there\"}],\"eid\":\"panelDEF\"}\n"
                "    ]\n"
                "}\n"
                );
    // Given
    uc->create_workspace("defaultWorkspace");
    // Given
    QScopedPointer<adapters::ProjectJson> jsonAdapter(new adapters::ProjectJson());
    jsonAdapter->setUsecases(uc.data());
    // Given
    QSignalSpy loaded(jsonAdapter.data(), SIGNAL(loaded(int)));
    jsonAdapter->loadFromJsonDoc(projectJsonDoc);
    loaded.wait(200);
    // Given
    QScopedPointer<adapters::ProjectPdf> adapter(new adapters::ProjectPdf());
    adapter->setUsecases(uc.data());
    // When
    QSignalSpy saved(adapter.data(), SIGNAL(saved(const QString&)));
    adapter->saveToPdf("myFile.pdf");
    saved.wait(200);
    if (!saved.first().isEmpty() && saved.first().count() > 0) {
        auto outputFilePath = saved.first().at(0).toString();
        // Then
        QVERIFY(QFileInfo::exists(outputFilePath));
        // output file has pdf extension
        QFAIL("not implemented");
        // output file has PDF mime type
        QFAIL("not implemented");
    } else {
        QFAIL("");
    }
}

QTEST_MAIN(ProjectPdfTest)

#include "tst_project_pdf.moc"
