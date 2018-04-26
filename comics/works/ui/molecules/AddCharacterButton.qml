import QtQuick 2.0

Rectangle {
    id: addCharacterButton
    signal clicked(var mouse)
    width: 40
    height: width
    color: "#666"
    Image {
        anchors.fill: parent
        source: Qt.resolvedUrl("../assets/cw-icons-character.png")
    }
    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked(mouse)
    }
}
