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
    void test_removeDialog();
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

void PanelTest::test_removeDialog()
{
    // GIVEN
    QScopedPointer<Panel> panel(new Panel("someId"));
    // GIVEN
    auto dialogId = "dialog1";
    auto dialogContent_en_US = "hello world";
    auto characterName = "Ayran";
    panel->addDialog(dialogId, dialogContent_en_US, characterName);
    QCOMPARE(panel->dialogs().size(), 1);
    // WHEN
    panel->removeDialog(dialogId);
    // THEN
    QCOMPARE(panel->dialogs().size(), 0);
}

QTEST_APPLESS_MAIN(PanelTest)

#include "tst_panel.moc"
