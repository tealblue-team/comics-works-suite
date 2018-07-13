#include <QString>
#include <QObject>
#include <QtTest>
#include <QJsonDocument>
#include "project_json.h"
#include "comics/works/usecases/usecases.h"
#include "comics/works/entities/register.h"
#include "comics/works/entities/character/character_base.h"
#include "comics/works/entities/project/project_base.h"

using namespace comics::works;

class ProjectJsonTest : public QObject
{
    Q_OBJECT

public:
    ProjectJsonTest();

private Q_SLOTS:
    void test_loadFromJsonDoc();
    void test_saveToJsonDoc();

    void test_readJsonFromFile();
    void test_writeJsonToFile();
};

ProjectJsonTest::ProjectJsonTest()
{
}

void ProjectJsonTest::test_loadFromJsonDoc()
{
    // Given
    entities::Register entities_register;
    QScopedPointer<usecases> uc(new usecases());
    uc->entities_reg = &entities_register;
    // Given
    QByteArray projectJsonDoc(
                "{"
                "\"characters\":[{\"name\":\"Ayran\"},{\"name\":\"Birun\"},{\"name\":\"Dilgun\"},{\"name\":\"Barsun\"}],"
                "\"panels\":["
                "{\"characters\":[\"Ayran\",\"Birun\"],\"description\":\"first scene\",\"dialogs\":[{\"characterName\":\"Ayran\",\"dialogContent_en_US\":\"Hello\"},{\"characterName\":\"Birun\",\"dialogContent_en_US\":\"Hi\"}],\"eid\":\"panelABC\",\"name\":\"HL-I-1\"},"
                "{\"characters\":[\"Barsun\",\"Dilgun\"],\"description\":\"second scene\",\"dialogs\":[{\"characterName\":\"Dilgun\",\"dialogContent_en_US\":\"Hey\"},{\"characterName\":\"Barsun\",\"dialogContent_en_US\":\"Hey there\"}],\"eid\":\"panelDEF\"}"
                "]"
                "}"
                );
    // Given
    uc->create_project("defaultWorkspace");
    // Given
    QScopedPointer<adapters::ProjectJson> adapter(new adapters::ProjectJson());
    adapter->setUsecases(uc.data());
    // When
    QSignalSpy loaded(adapter.data(), SIGNAL(loaded(int)));
    adapter->loadFromJsonDoc(projectJsonDoc);
    loaded.wait(200);
    // Then
    auto characters = uc->entities_reg->currentProject->characters();
    QVERIFY(characters);
    QCOMPARE(characters->length(), 4);
    // And
    auto panels = uc->entities_reg->currentProject->panels();
    QVERIFY(panels);
    QCOMPARE(panels->length(), 2);
    // And
    QCOMPARE(panels->at(0)->eid(), "panelABC");
    QCOMPARE(panels->at(0)->name(), "HL-I-1");
    QCOMPARE(panels->at(0)->description(), "first scene");
    QCOMPARE(panels->at(0)->characters()->length(), 2);
    QCOMPARE(panels->at(0)->characters()->at(0)->name(), QString("Ayran"));
    QCOMPARE(panels->at(0)->characters()->at(1)->name(), QString("Birun"));
    QCOMPARE(panels->at(0)->dialogs().length(), 2);
    QCOMPARE(panels->at(0)->dialogs().at(0).toMap().value("characterName"), QString("Ayran"));
    QCOMPARE(panels->at(0)->dialogs().at(0).toMap().value("dialogContent_en_US"), QString("Hello"));
    QCOMPARE(panels->at(0)->dialogs().at(1).toMap().value("characterName"), QString("Birun"));
    QCOMPARE(panels->at(0)->dialogs().at(1).toMap().value("dialogContent_en_US"), QString("Hi"));
    // And
    QCOMPARE(panels->at(1)->eid(), "panelDEF");
    QCOMPARE(panels->at(1)->description(), "second scene");
    QCOMPARE(panels->at(1)->characters()->length(), 2);
    QCOMPARE(panels->at(1)->characters()->at(0)->name(), QString("Barsun"));
    QCOMPARE(panels->at(1)->characters()->at(1)->name(), QString("Dilgun"));
    QCOMPARE(panels->at(1)->dialogs().length(), 2);
    QCOMPARE(panels->at(1)->dialogs().at(0).toMap().value("characterName"), QString("Dilgun"));
    QCOMPARE(panels->at(1)->dialogs().at(0).toMap().value("dialogContent_en_US"), QString("Hey"));
    QCOMPARE(panels->at(1)->dialogs().at(1).toMap().value("characterName"), QString("Barsun"));
    QCOMPARE(panels->at(1)->dialogs().at(1).toMap().value("dialogContent_en_US"), QString("Hey there"));
}

void ProjectJsonTest::test_saveToJsonDoc()
{
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
                "        {\"characters\":[\"Barsun\",\"Dilgun\"],\"description\":\"second scene\",\"dialogs\":[{\"characterName\":\"Dilgun\",\"dialogContent_en_US\":\"Hey\"},{\"characterName\":\"Barsun\",\"dialogContent_en_US\":\"Hey there\"}],\"eid\":\"panelDEF\",\"name\":\"\"}\n"
                "    ]\n"
                "}\n"
                );
    // Given
    uc->create_project("defaultWorkspace");
    // Given
    QScopedPointer<adapters::ProjectJson> adapter(new adapters::ProjectJson());
    adapter->setUsecases(uc.data());
    // Given
    QSignalSpy loaded(adapter.data(), SIGNAL(loaded(int)));
    adapter->loadFromJsonDoc(projectJsonDoc);
    loaded.wait(200);
    // When
    QSignalSpy saved(adapter.data(), SIGNAL(saved(QByteArray)));
    adapter->saveToJsonDoc();
    saved.wait(200);
    if (!saved.first().isEmpty() && saved.first().count() > 0) {
        qDebug() << saved.first().at(0).toByteArray();
        qDebug() << QJsonDocument::fromJson(projectJsonDoc).toJson(QJsonDocument::Indented);
        QCOMPARE(saved.first().at(0).toByteArray(),QJsonDocument::fromJson(projectJsonDoc).toJson(QJsonDocument::Indented));
    } else {
        QFAIL("");
    }
}

void ProjectJsonTest::test_readJsonFromFile()
{
    // Given
    QScopedPointer<adapters::ProjectJson> adapter(new adapters::ProjectJson());
    // Given
    const QString fileName(":/qt-project.org/imports/testProject1.cw.json");
    // Given
    QByteArray expectedProjectJson(
                "{\n"
                "    \"characters\":[{\"name\":\"Ayran\"},{\"name\":\"Birun\"},{\"name\":\"Dilgun\"},{\"name\":\"Barsun\"}],\n"
                "    \"panels\":[\n"
                "        {\"characters\":[\"Ayran\",\"Birun\"],\"description\":\"first scene\",\"dialogs\":[{\"characterName\":\"Ayran\",\"dialogContent_en_US\":\"Hello\"},{\"characterName\":\"Birun\",\"dialogContent_en_US\":\"Hi\"}],\"eid\":\"panelABC\",\"name\":\"HL-I-1\"},\n"
                "        {\"characters\":[\"Barsun\",\"Dilgun\"],\"description\":\"second scene\",\"dialogs\":[{\"characterName\":\"Dilgun\",\"dialogContent_en_US\":\"Hey\"},{\"characterName\":\"Barsun\",\"dialogContent_en_US\":\"Hey there\"}],\"eid\":\"panelDEF\"}\n"
                "    ]\n"
                "}\n"
                );
    // When
    auto actualProjectJson = adapter->readJsonFromFile(fileName);
    // Then
    QCOMPARE(actualProjectJson, expectedProjectJson);
}

void ProjectJsonTest::test_writeJsonToFile()
{
    // Given
    QScopedPointer<adapters::ProjectJson> adapter(new adapters::ProjectJson());
    // Given
    const QString fileName("testProject2.cw.json");
    // Given
    QByteArray projectJson(
                "{\n"
                "    \"characters\":[{\"name\":\"Ayran\"},{\"name\":\"Birun\"},{\"name\":\"Dilgun\"},{\"name\":\"Barsun\"}],\n"
                "    \"panels\":[\n"
                "        {\"characters\":[\"Ayran\",\"Birun\"],\"description\":\"first scene\",\"dialogs\":[{\"characterName\":\"Ayran\",\"dialogContent_en_US\":\"Hello\"},{\"characterName\":\"Birun\",\"dialogContent_en_US\":\"Hi\"}],\"eid\":\"panelABC\",\"name\":\"HL-I-1\"},\n"
                "        {\"characters\":[\"Barsun\",\"Dilgun\"],\"description\":\"second scene\",\"dialogs\":[{\"characterName\":\"Dilgun\",\"dialogContent_en_US\":\"Hey\"},{\"characterName\":\"Barsun\",\"dialogContent_en_US\":\"Hey there\"}],\"eid\":\"panelDEF\",\"name\":\"}\n"
                "    ]\n"
                "}\n"
                );
    // When
    bool success = adapter->writeJsonToFile(projectJson, fileName) == fileName;
    // Then
    QCOMPARE(success, true);
    QCOMPARE(adapter->readJsonFromFile(fileName), projectJson);
}

QTEST_MAIN(ProjectJsonTest)

#include "tst_project_json.moc"
