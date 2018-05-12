import QtQuick 2.0
import "." as CWA

Item {
    id: addCharacterBadge
    signal clicked(var mouse)
    property string text
    width: 32
    height: width
    Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: Colors.shades400
    }
    CWA.Icon {
        content: "add"
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked(mouse)
    }
}
