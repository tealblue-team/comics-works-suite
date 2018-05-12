import QtQuick 2.0

Item {
    property string content
    Image {
        width: 16
        height: width
        anchors.centerIn: parent
        source: Qt.resolvedUrl("../assets/icons/%1.svg".arg(content))
    }
    width: 24
    height: width
}
