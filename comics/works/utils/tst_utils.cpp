#include <QString>
#include <QtTest>
#include "utils.h"

using namespace comics::works;

class UtilsTest : public QObject
{
    Q_OBJECT

public:
    UtilsTest();

private Q_SLOTS:
    void test_generateRandomId();
};

UtilsTest::UtilsTest()
{
}

void UtilsTest::test_generateRandomId()
{
    QScopedPointer<Utils> utils(new Utils());
    QCOMPARE(utils->generateRandomId(5).size(),5);
}

QTEST_APPLESS_MAIN(UtilsTest)

#include "tst_utils.moc"
