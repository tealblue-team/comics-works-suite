#include <QString>
#include <QObject>
#include <QtTest>
#include <QJsonDocument>
#include "project_json.h"
#include "comics/works/usecases/usecases.h"
#include "comics/works/entities/register.h"

using namespace comics::works;

class ProjectJsonTest : public QObject
{
    Q_OBJECT

public:
    ProjectJsonTest();

private Q_SLOTS:
    void test_loadFromJsonDoc();
    void test_saveToJsonDoc();
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
                "{\"characters\":[\"Ayran\",\"Birun\"],\"description\":\"first scene\",\"dialogs\":[{\"characterName\":\"Ayran\",\"dialogContent_en_US\":\"Hello\"},{\"characterName\":\"Birun\",\"dialogContent_en_US\":\"Hi\"}],\"eid\":\"panel1\"},"
                "{\"characters\":[\"Barsun\",\"Dilgun\"],\"description\":\"second scene\",\"dialogs\":[{\"characterName\":\"Dilgun\",\"dialogContent_en_US\":\"Hey\"},{\"characterName\":\"Barsun\",\"dialogContent_en_US\":\"Hey there\"}],\"eid\":\"panel2\"}"
                "]"
                "}"
                );
    // Given
    uc->create_workspace("defaultWorkspace");
    // Given
    QScopedPointer<adapters::ProjectJson> adapter(new adapters::ProjectJson(uc.data()));
    // When
    QSignalSpy loaded(adapter.data(), SIGNAL(loaded(int)));
    adapter->loadFromJsonDoc(projectJsonDoc);
    loaded.wait(200);
    // Then
    auto characters = uc->entities_reg->currentWorkspace->characters();
    QVERIFY(characters);
    QCOMPARE(characters->length(), 4);
    // And
    auto panels = uc->entities_reg->currentWorkspace->panels();
    QVERIFY(panels);
    QCOMPARE(panels->length(), 2);
    // And
    QCOMPARE(panels->at(0)->eid(), "panel1");
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
    QCOMPARE(panels->at(1)->eid(), "panel2");
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
                "{"
                "\"characters\":[{\"name\":\"Ayran\"},{\"name\":\"Birun\"},{\"name\":\"Dilgun\"},{\"name\":\"Barsun\"}],"
                "\"panels\":["
                "{\"characters\":[\"Ayran\",\"Birun\"],\"description\":\"first scene\",\"dialogs\":[{\"characterName\":\"Ayran\",\"dialogContent_en_US\":\"Hello\"},{\"characterName\":\"Birun\",\"dialogContent_en_US\":\"Hi\"}],\"eid\":\"panel1\"},"
                "{\"characters\":[\"Barsun\",\"Dilgun\"],\"description\":\"second scene\",\"dialogs\":[{\"characterName\":\"Dilgun\",\"dialogContent_en_US\":\"Hey\"},{\"characterName\":\"Barsun\",\"dialogContent_en_US\":\"Hey there\"}],\"eid\":\"panel2\"}"
                "]"
                "}"
                );
    // Given
    uc->create_workspace("defaultWorkspace");
    // Given
    QScopedPointer<adapters::ProjectJson> adapter(new adapters::ProjectJson(uc.data()));
    // Given
    QSignalSpy loaded(adapter.data(), SIGNAL(loaded(int)));
    adapter->loadFromJsonDoc(projectJsonDoc);
    loaded.wait(200);
    // When
    QSignalSpy saved(adapter.data(), SIGNAL(saved(QByteArray)));
    adapter->saveToJsonDoc(entities_register);
    saved.wait(200);
    if (!saved.first().isEmpty() && saved.first().count() > 0) {
        QCOMPARE(saved.first().at(0).toByteArray(),projectJsonDoc);
    } else {
        QFAIL("");
    }
}

QTEST_MAIN(ProjectJsonTest)

#include "tst_project_json.moc"
