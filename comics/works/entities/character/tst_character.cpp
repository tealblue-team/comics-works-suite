#include <QString>
#include <QtTest>
#include "character.h"

using namespace comics::works;

class CharacterTest : public QObject
{
    Q_OBJECT

public:
    CharacterTest();

private Q_SLOTS:
    void test_create();
    void test_name();
};

CharacterTest::CharacterTest()
{
}

void CharacterTest::test_create()
{
    QScopedPointer<entities::Character> character(new entities::Character("aName",this));
    QVERIFY(character.data());
}

void CharacterTest::test_name()
{
    QScopedPointer<entities::Character> character(new entities::Character("aName",this));
    QCOMPARE(character.data()->name(), QString("aName"));
}

QTEST_APPLESS_MAIN(CharacterTest)

#include "tst_character.moc"
