import QtQuick 2.10
import QtQuick.Controls 2.3
import "../atoms" as CWA

Rectangle {
    id: root
    signal addCharacterFieldReturnPressed(var event)
    signal itemClicked(string name)
    property alias model: listView.model
    property alias addCharacterField: addCharacterField
    width: childrenRect.width
    height: childrenRect.height
    color: CWA.Colors.shades600
    Column {
        width: parent.width
        height: childrenRect.height
        Row {
            id: header
            spacing: 8
            height: childrenRect.height
            width: childrenRect.width
            CWA.Icon {
                content: "characters"
            }
            CWA.H6 {
                text: qsTr("Characters")
                color: CWA.Colors.shades400
            }
        }
        TextField {
            id: addCharacterField
            color: CWA.Colors.shades0
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 40
                color: "transparent"
                border.color: "transparent"
                CWA.P2 {
                    color: CWA.Colors.shades0
                    opacity: .5
                    text: qsTr("add character...")
                    anchors.verticalCenter: parent.verticalCenter
                    visible: ! addCharacterField.displayText
                }
            }
            Keys.onReturnPressed: addCharacterFieldReturnPressed(event)
        }
        ListView {
            id: listView
            model: [{"name":"first character"},{"name":"second character"}]
            spacing: 4
            clip: true
            height: 180
            anchors.left: parent.left
            anchors.right: parent.right
            delegate: Item {
                width: parent.width
                height: 20
                CWA.P2 {
                    text: modelData.name
                    color: CWA.Colors.shades0
                    anchors.verticalCenter: parent.verticalCenter
                }
                MouseArea {
                    anchors.right: parent.right
                    width: 24
                    height: 24
                    onClicked: itemClicked(modelData.name)
                    CWA.Icon {
                        content: "remove"
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }
}
