import QtQuick 2.0
import QtQuick.Controls 2.3

Rectangle {
    id: root
    signal itemClicked(string name)
    property alias model: repeater.model
    width: 80
    height: repeater.count * 24 + 8
    color: Colors.shades200
    Column {
        anchors.fill: parent
        anchors.margins: 4
        Repeater {
            id: repeater
            model: typeof(modelData) != "undefined" ? modelData.characters : [{"name":"first character"},{"name":"second character"}]
            delegate: ItemDelegate {
                padding: 0
                text: modelData.name
                font.pixelSize: Typo.p2
                onClicked: {
                    itemClicked(modelData.name)
                }
                width: parent.width
                height: 24
            }
        }
    }
}
