import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: icon
    property string content: "panel"
    Image {
        id: iconImage
        width: 16
        height: width
        anchors.centerIn: parent
        source: Qt.resolvedUrl("../assets/icons/%1.svg".arg(content))
    }
    Colorize {
        anchors.fill: iconImage
        source: iconImage
        saturation: 0
        lightness: 1.2
    }
    width: 24
    height: width
}
