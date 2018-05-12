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
    GridLayout {
        anchors.fill: parent
        anchors.margins: 16
        columns: 2
        ColumnLayout {
            Layout.columnSpan: 2
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
        ColumnLayout {
            Label {
                text: "Typography"
            }
            Column {
                spacing: 8
                CWA.H1 {text:"Heading 1"}
                CWA.H2 {text:"Heading 2"}
                CWA.H3 {text:"Heading 3"}
                CWA.H4 {text:"Heading 4"}
                CWA.H5 {text:"Heading 5"}
                CWA.H6 {text:"Heading 6"}
                CWA.P1 {text:"Paragraph 1"}
                CWA.P2 {text:"Paragraph 2"}
            }
        }
        ColumnLayout {
            Label {
                text: "Icons"
            }
            Grid {
                spacing: 8
                rows: 2
                Repeater {
                    model: CWA.Icons.content
                    delegate: Column {
                        Rectangle {
                            color: CWA.Colors.shades50
                            height: childrenRect.height
                            width: childrenRect.width
                            CWA.Icon {
                                content: modelData
                            }
                        }
                        CWA.P2 {
                            text: modelData
                        }
                    }
                }
            }
        }
    }
}
