import QtQuick 2.10
import QtQuick.Controls 2.3
import "../atoms" as CWA
import "../molecules" as CWM

FocusScope {
    id: root
    signal removePanelButtonClicked(string itemId)
    signal panelClicked(int idx)
    property alias model: listView.model
    property alias addPanelButton: addPanelButton
    implicitWidth: 256
    implicitHeight: 256
    Rectangle {
        anchors.fill: parent
        color: CWA.Colors.shades600
    }
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
    CWM.InlineTextIconButton {
        id: addPanelButton
        anchors.top: header.bottom
        focus: true
        text: qsTr("add panel")
        iconContent: "add"
        anchors{left:parent.left;right:parent.right}
        Keys.onReturnPressed: clicked()
    }
    ListView {
        id: listView
        signal itemClicked()
        clip: true
        height: 180
        anchors.top: addPanelButton.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        model: ListModel{
            ListElement {eid:"pABCDE";description:"desc1";name:"panel 1"}
            ListElement {eid:"pABCDE";description:"desc2"}
        }
        delegate: Item {
            width: root.width
            height: childrenRect.height
            CWA.P3 {
                id: nameLabel
                text: model.name || "[%1]".arg(model.eid)
                color: CWA.Colors.shades0
                opacity: .8
                width: 64
                elide: Text.ElideRight
                font.pixelSize: 11
                anchors.verticalCenter: descriptionLabel.verticalCenter
                verticalAlignment: Qt.AlignVCenter
            }
            CWA.P3 {
                id: descriptionLabel
                text: model.description || ""
                color: CWA.Colors.shades0
                elide: Text.ElideRight
                width: root.width - 88
                anchors.left: nameLabel.right
                verticalAlignment: Qt.AlignVCenter
            }
            MouseArea {
                anchors.fill: parent
                onClicked: panelClicked(index)
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
