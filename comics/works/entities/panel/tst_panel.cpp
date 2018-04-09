#include <QString>
#include <QtTest>
#include "panel.h"

using namespace comics::works::entities;

class PanelTest : public QObject
{
    Q_OBJECT

public:
    PanelTest();

private Q_SLOTS:
    void test_create();
};

PanelTest::PanelTest()
{
}

void PanelTest::test_create()
{
    // WHEN
    QScopedPointer<Panel> panel(new Panel("someId"));
    // THEN
    QCOMPARE(panel->eid(),QString("someId"));
}

QTEST_APPLESS_MAIN(PanelTest)

#include "tst_panel.moc"
