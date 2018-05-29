import QtQuick 2.10
import QtQuick.Controls 2.3
import "../atoms" as CWA

Rectangle {
    id: root
    signal addCharacterFieldReturnPressed(var event)
    signal itemClicked(string name)
    property alias model: listView.model
    property alias addCharacterField: addCharacterField
    implicitWidth: 256
    implicitHeight: 256
    color: CWA.Colors.shades600
    Row {
        id: header
        spacing: 8
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
        anchors.top: header.bottom
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
        model: ListModel {
            ListElement {name:"first character"}
            ListElement {name:"second character"}
        }
        spacing: 4
        clip: true
        anchors.top: addCharacterField.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        delegate: Item {
            width: parent.width
            height: 20
            CWA.P2 {
                text: model.name
                color: CWA.Colors.shades0
                anchors.verticalCenter: parent.verticalCenter
            }
            MouseArea {
                anchors.right: parent.right
                width: 24
                height: 24
                onClicked: itemClicked(model.name)
                CWA.Icon {
                    content: "remove"
                    anchors.centerIn: parent
                }
            }
        }
    }
}
