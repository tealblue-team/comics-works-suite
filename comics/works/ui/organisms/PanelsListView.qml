import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "../atoms" as CWA
import "../molecules" as CWM
import "../organisms" as CWO

ListView {
    id: panelsListView
    clip: true
    delegate: Row {
        spacing: 4
        width: panelsListView.width
        CWA.P2 {
            text: modelData.eid
            color: CWA.Colors.shades0
            opacity: .8
            width: 56
        }
        CWA.P2 {
            text: modelData.description
            color: CWA.Colors.shades0
            elide: Text.ElideRight
            width: panelsListView.width - 64
        }
    }
    header: Column {
        width: panelsListView.width
        Item {
            width: parent.width
            height: 20
            CWA.P2 {
                id: addPanelButton
                text: qsTr("add panel")
                color: CWA.Colors.shades0
                opacity: .5
                MouseArea {
                    anchors.fill: parent
                    onClicked: uc.create_panel("panel"+(panelsGrid.model.length+1), workspaceName)
                }
            }
            CWA.Icon {
                content: "add"
                anchors.right: parent.right
            }
        }
        Item {
            width: parent.width
            height: 20
            CWA.P2 {
                id: removePanelButton
                text: qsTr("remove last panel")
                color: CWA.Colors.shades0
                opacity: .5
                MouseArea {
                    anchors.fill: parent
                    onClicked: uc.delete_panel("panel"+(panelsGrid.model.length), workspaceName)
                }
                enabled: panelsGrid.model.length > 0
            }
            CWA.Icon {
                content: "remove"
                anchors.right: parent.right
            }
        }
    }
}
