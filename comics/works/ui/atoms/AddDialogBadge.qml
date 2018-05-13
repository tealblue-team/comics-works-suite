import QtQuick 2.0
import "." as CWA

Item {
    id: addDialogBadge
    signal clicked(var mouse)
    property string text
    width: 24
    height: width
    Rectangle {
        anchors.fill: parent
        radius: width / 2
        color: Colors.shades400
    }
    CWA.Icon {
        content: "dialog"
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked(mouse)
    }
}
