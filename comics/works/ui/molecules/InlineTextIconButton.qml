import QtQuick 2.0
import QtQuick.Controls 2.3
import "../atoms" as CWA

Button {
    id: root
    property alias iconContent: iconEl.content
    implicitWidth: 120
    height: 24
    background: Rectangle {
        color: pressed ? CWA.Colors.shades400 : "transparent"
    }
    contentItem: Item {
        anchors.fill: parent
        TextField { // fix to get proper focus
            text: root.text || "[text]"
            color: activeFocus ? CWA.Colors.primary500 : CWA.Colors.shades0
            opacity: activeFocus ? 1 : .5
            anchors.verticalCenter: parent.verticalCenter
            background: Item{}
            cursorDelegate: Item{}
        }
        CWA.Icon {
            id: iconEl
            content: "add"
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
