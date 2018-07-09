import QtQuick 2.10
import QtQuick.Controls 2.3
import "../atoms" as CWA
import "../molecules" as CWM

FocusScope {
    id: root
    signal removePanelButtonClicked(string itemId)
    property alias model: listView.model
    property alias addPanelButton: addPanelButton
    Rectangle {
        anchors.fill: parent
        color: CWA.Colors.shades600
    }
    implicitWidth: 256
    implicitHeight: 256
    Row {
        id: header
        spacing: 8
        CWA.Icon {
            content: "panel"
        }
        CWA.H6 {
            text: qsTr("Panels")
            color: CWA.Colors.shades400
        }
    }
    Column {
        id: buttonsCol
        width: root.width
        anchors.top: header.bottom
        CWM.InlineTextIconButton {
            id: addPanelButton
            focus: true
            text: qsTr("add panel")
            iconContent: "add"
            anchors{left:parent.left;right:parent.right}
            Keys.onReturnPressed: clicked()
        }
    }
    ListView {
        id: listView
        clip: true
        height: 180
        anchors.top: buttonsCol.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        model: ListModel{
            ListElement {eid:"panel1";description:"desc1"}
            ListElement {eid:"panel2";description:"desc2"}
        }
        delegate: Item {
            width: root.width
            height: childrenRect.height
            CWA.P2 {
                id: nameLabel
                text: model.name || "[%1]".arg(model.eid)
                color: CWA.Colors.shades0
                opacity: .8
                width: 56
            }
            CWA.P2 {
                id: descriptionLabel
                text: model.description
                color: CWA.Colors.shades0
                elide: Text.ElideRight
                width: root.width - 64
                anchors.left: nameLabel.right
            }
            MouseArea {
                anchors.right: parent.right
                width: 24
                height: 24
                onClicked: removePanelButtonClicked(model.eid)
                CWA.Icon {
                    content: "remove"
                    anchors.centerIn: parent
                }
            }
        }
    }
}
