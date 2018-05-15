import QtQuick 2.0
import QtQuick.Controls 2.3

RoundButton {
    id: root
    property string size
    width: size === "S" ? 24 : 32
    height: width
    radius: width / 2
    background: Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: pressed ? Colors.shades500 : Colors.shades400
    }
    contentItem: P2 {
        font.pixelSize: size == "S" ? Typo.p3 : Typo.p2
        text: root.text.substring(0,3)
        width: 24
        height: width
        anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: Colors.shades0
    }
}
