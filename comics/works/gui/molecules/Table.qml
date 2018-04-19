import QtQuick 2.0

Item {
    id: tableSurface
    width: 800
    height: 600

    property alias columns: panelsContainer.columns
    property alias rows: panelsContainer.rows

    default property alias panels: panelsContainer.children

    Rectangle {
        anchors.fill: parent
        color: "dimgray"
    }

    Grid {
        id: panelsContainer
        spacing: 8
        anchors.fill: parent
        anchors.margins: 16
    }
}
