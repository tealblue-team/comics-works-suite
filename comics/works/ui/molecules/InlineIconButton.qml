import QtQuick 2.0
import QtQuick.Controls 2.3
import "../atoms" as CWA

RoundButton {
    id: root
    property string size
    property alias iconContent: icon.content
    implicitWidth: size == "S" ? 24 : 32
    implicitHeight: width
    radius: width / 2
    contentItem: CWA.Icon {
        id: icon
        content: "add"
        anchors.centerIn: parent
    }
    background: Rectangle {
        width: root.width
        height: root.height
        radius: root.radius
        color: pressed ? CWA.Colors.shades500 : CWA.Colors.shades400
    }
}
