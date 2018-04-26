import QtQuick 2.0

Rectangle {
    id: addDialogButton
    signal clicked(var mouse)
    width: 40
    height: width
    color: "#666"
    Image {
        anchors.fill: parent
        source: Qt.resolvedUrl("../assets/cw-icons-bubble.png")
    }
    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked(mouse)
    }
}
