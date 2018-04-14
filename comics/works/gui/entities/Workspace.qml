import QtQuick 2.0

Item {
    id: tableSurface
    width: 800
    height: 600

    default property alias panels: panels.children

    Rectangle {
        anchors.fill: parent
        color: "dimgray"
    }

    Column {
        id: panels
        spacing: 8
        anchors.centerIn: parent
    }
}
