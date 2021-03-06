import QtQuick 2.0
import QtQuick.Controls 2.3
import "../atoms" as CWA

Label {
    id: root
    property alias timer: timer
    padding: 6
    background: Rectangle {color: CWA.Colors.shades600;radius:4}
    color: CWA.Colors.shades0
    font.pixelSize: CWA.Typo.p2
    width: 256
    height: implicitHeight
    horizontalAlignment: Label.AlignHCenter
    text: "[snackbar text, can span up to two lines]"
    wrapMode: Text.Wrap
    Timer {
        id: timer
        interval: 2500
        running: true
        onTriggered: parent.visible = false
    }
}
