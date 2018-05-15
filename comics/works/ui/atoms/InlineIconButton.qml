import QtQuick 2.0
import QtQuick.Controls 2.3
import "." as CWA

RoundButton {
    id: root
    property string size
    width: size == "S" ? 24 : 32
    height: width
    radius: width / 2
    contentItem: CWA.Icon {
        content: "add"
        anchors.centerIn: parent
    }
    background: Rectangle {
        width: root.width
        height: root.height
        radius: root.radius
        color: pressed ? Colors.shades500 : Colors.shades400
    }
}
