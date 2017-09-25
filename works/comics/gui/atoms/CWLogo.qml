import QtQuick 2.0

Item {
    id: logo
    width: 64
    height: width
    Image {
        width: logo.width
        height: logo.height
        source: Qt.resolvedUrl("../assets/atoms-CWLogo--cog.svg")
        sourceSize: Qt.size(logo.width, logo.height)
        RotationAnimation on rotation {
            loops: Animation.Infinite
            from: 360
            to: 0
            duration: 7000
        }
    }
    Image {
        width: logo.width
        height: logo.height
        source: Qt.resolvedUrl("../assets/atoms-CWLogo--bubble.svg")
        sourceSize: Qt.size(logo.width, logo.height)
    }
}
