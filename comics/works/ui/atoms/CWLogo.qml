import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id: logo
    width: 64*3
    height: width
    Image {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 16
        width: logo.width * 0.6
        height: width
        source: Qt.resolvedUrl("../assets/comicsworks-logo-cog-big.svg")
        sourceSize: Qt.size(logo.width, logo.height)
        RotationAnimation on rotation {
            loops: Animation.Infinite
            from: 360
            to: 0
            duration: 20000 / 4.065
        }
    }
    Image {
        id: cogSmall
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 16
        width: logo.width * 0.4
        height: width
        source: Qt.resolvedUrl("../assets/comicsworks-logo-cog-small.svg")
        sourceSize: Qt.size(logo.width, logo.height)
        rotation: 10
        RotationAnimation on rotation {
            loops: Animation.Infinite
            from: 0
            to: 360
            duration: 20000 / 6
            running: true
        }
    }
    Image {
        width: logo.width
        height: logo.height
        source: Qt.resolvedUrl("../assets/comicsworks-logo-bubbles.svg")
        sourceSize: Qt.size(logo.width, logo.height)
    }
}
