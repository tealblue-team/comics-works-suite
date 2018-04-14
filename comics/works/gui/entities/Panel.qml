import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

Item {
    id: panel

    width: 256
    height: width

    property alias panelName: panelName

    Rectangle {
        id: pageFace
        anchors.fill: parent
        color: "white"
    }
    DropShadow {
        source:pageFace
        anchors.fill: source
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8.0
        color: "#80000000"
    }

    Item {
        id: drawingSurface
        anchors.fill: parent
        anchors.margins: 32
    }
    Text {
        id: panelName
        anchors.horizontalCenter: parent.horizontalCenter
        text: "[panel name]"
        opacity: .8
    }
}

