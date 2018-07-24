import QtQuick 2.10
import QtQuick.Controls 2.2
import "../atoms" as CWA

TextField {
    id: projectNameLabel
    signal nameConfirmed(var event)
    text: "[projectName]"
    color: focus ? CWA.Colors.primary500 : CWA.Colors.shades300
    font.pixelSize: CWA.Typo.h6
    background: Item {}
    leftPadding: 0
    Keys.onReturnPressed: nameConfirmed(event)
    CWA.P2 {
        color: CWA.Colors.shades400
        text: parent.placeholderText
        anchors.verticalCenter: parent.verticalCenter
        visible: ! parent.displayText
    }
}
