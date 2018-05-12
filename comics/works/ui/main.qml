import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.10
import comics.works.ui.atoms 1.0 as CWA

Window {
    visible: true
    width: 1024
    height: 768
    title: qsTr("comics.works UI")
    ColumnLayout {
        Label {
            text: "Colors"
        }
        Grid {
            columns: 5
            rows: 2
            spacing: 8
            Repeater {
                model: [
                    "shades0",
                    "shades50",
                    "shades100",
                    "shades200",
                    "shades300",
                    "shades400",
                    "shades500",
                    "shades600",
                    "shades700",
                    "shades900"
                ]
                delegate: Rectangle {
                    width: 160
                    height: 120
                    color: CWA.Colors[modelData]
                    Text {
                        anchors.centerIn: parent
                        text: "%1\n%2".arg(modelData).arg(CWA.Colors[modelData])
                        horizontalAlignment: Text.AlignHCenter
                        color: index < 5 ? "#000" : "#fff"
                    }
                }
            }
        }
    }
}
