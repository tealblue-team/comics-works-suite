import QtQuick 2.10
import QtQuick.Controls 2.3
import "../atoms" as CWA
import "../molecules" as CWM

Rectangle {
    id: root
    signal itemClicked(string name)
    property alias model: listView.model
    property alias addPanelButton: addPanelButton
    property alias removePanelButton: removePanelButton
    implicitWidth: childrenRect.width
    implicitHeight: 200
    color: CWA.Colors.shades600
    Column {
        id: buttonsCol
        width: root.width
        CWM.InlineTextIconButton {
            id: addPanelButton
            text: qsTr("add panel")
            iconContent: "add"
            anchors{left:parent.left;right:parent.right}
        }
        CWM.InlineTextIconButton {
            id: removePanelButton
            text: qsTr("remove last panel")
            iconContent: "remove"
            anchors{left:parent.left;right:parent.right}
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
        delegate: Row {
            spacing: 4
            width: root.width
            CWA.P2 {
                text: model.eid
                color: CWA.Colors.shades0
                opacity: .8
                width: 56
            }
            CWA.P2 {
                text: model.description
                color: CWA.Colors.shades0
                elide: Text.ElideRight
                width: root.width - 64
            }
        }
    }
}
