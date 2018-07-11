import QtQuick 2.0
import QtQuick.Controls 2.3
import "../atoms" as CWA

RoundButton {
    id: root
    property string size
    implicitWidth: size === "S" ? 24 : 32
    implicitHeight: width
    radius: width / 2
    background: Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: parent.activeFocus ? CWA.Colors.primary500 :
                   pressed ? CWA.Colors.shades500 : CWA.Colors.shades400
    }
    contentItem: CWA.P2 {
        font.pixelSize: size == "S" ? CWA.Typo.p3 : CWA.Typo.p2
        text: root.text.substring(0,3)
        width: 24
        height: width
        anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: CWA.Colors.shades0
    }
}
