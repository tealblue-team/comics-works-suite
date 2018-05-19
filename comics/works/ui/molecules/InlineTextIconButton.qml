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
        CWA.P2 {
            text: root.text || "[text]"
            color: pressed ? CWA.Colors.shades700 : CWA.Colors.shades0
            opacity: .5
            anchors.verticalCenter: parent.verticalCenter
        }
        CWA.Icon {
            id: iconEl
            content: "add"
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
