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
    void test_loadFromJson();
};

ProjectJsonTest::ProjectJsonTest()
{
}

void ProjectJsonTest::test_loadFromJson()
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
    QSignalSpy completed(adapter.data(), SIGNAL(completed(int)));
    adapter->loadFrom(projectJsonDoc);
    completed.wait(500);
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

QTEST_MAIN(ProjectJsonTest)

#include "tst_project_json.moc"
