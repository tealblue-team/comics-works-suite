import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3

FocusScope {
    id: panel

    width: 256
    height: width

    property alias name: name
    property alias description: description

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
        id: name
        anchors.horizontalCenter: parent.horizontalCenter
        text: "[panel name]"
        opacity: .8
    }
    TextField {
        id: description
        focus: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        placeholderText: "[panel description]"
        Keys.onEscapePressed: focus = false
    }
}

