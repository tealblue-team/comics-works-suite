import QtQuick 2.10
import "../atoms" as CWA

Item {
    id: appBadge
    signal clicked(var mouse)
    property alias appVersion: appVersionLabel.text
    width: sizer.width
    height: sizer.height
    Row {
        id: sizer
        spacing: 8
        CWA.CWLogoIcon {
            id: cwLogoIcon
            width: 40
        }
        Column {
            anchors.verticalCenter: cwLogoIcon.verticalCenter
            spacing: -8
            Row {
                CWA.H5 {
                    text: "comics."
                    color: CWA.Colors.accent500
                }
                CWA.H5 {
                    text: "works"
                    color: CWA.Colors.shades300
                }
            }
            Row {
                spacing: 8
                CWA.H5 {
                    text: "StoryTeller"
                    color: CWA.Colors.shades300
                }
                CWA.P3 {
                    id: appVersionLabel
                    anchors.bottom: parent.bottom
                    color: CWA.Colors.shades500
                    text: '[version]'
                }
            }
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: appBadge.clicked(mouse)
    }
}
