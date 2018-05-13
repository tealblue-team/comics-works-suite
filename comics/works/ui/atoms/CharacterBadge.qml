import QtQuick 2.0

Item {
    id: characterBadge
    property string text
    property string size: "M"
    signal clicked
    width: size === "M" ? 32 : 24
    height: width
    Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: Colors.shades400
    }
    P2 {
        id: nicknameLabel
        font.pixelSize: size == "M" ? Typo.p2 : 12
        text: characterBadge.text.substring(0,3)
        width: 24
        height: width
        anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: Colors.shades0
    }
    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked(mouse)
    }
}
