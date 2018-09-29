import QtQuick 2.10
import "../atoms" as CWA

Row {
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
                anchors.bottom: parent.bottom
                color: CWA.Colors.shades500
                text: typeof applicationVersion != 'undefined' ? applicationVersion : '[version]'
            }
        }
    }
}
