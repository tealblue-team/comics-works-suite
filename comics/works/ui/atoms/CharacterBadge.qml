import QtQuick 2.0

Item {
    id: characterBadge
    property string text
    width: 32
    height: width
    Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: Colors.shades400
    }
    P2 {
        id: nicknameLabel
        text: characterBadge.text.substring(0,3)
        width: 24
        height: width
        anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: Colors.shades0
    }
}
