import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Window 2.10
import comics.works.ui.atoms 1.0 as CWA
import comics.works.ui.molecules 1.0 as CWM

Window {
    visible: true
    width: 1024
    height: 768
    title: qsTr("comics.works UI")
    color: CWA.Colors.shades300
    SwipeView {
        id: view
        currentIndex: 0
        anchors.fill: parent
        GridLayout {
            id: firstpage
            width: view.width
            height: view.height
            columns: 4
            ColumnLayout {
                Layout.alignment: Qt.AlignTop
                Layout.margins: 8
                Layout.columnSpan: 3
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
                            width: 120
                            height: 90
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
                Layout.alignment: Qt.AlignTop
                Layout.margins: 8
                Label {
                    text: "Logotypes"
                }
                CWA.CWLogo {

                }
                Rectangle {
                    width: childrenRect.width
                    height: childrenRect.height
                    color: CWA.Colors.shades600
                    CWA.CWLogoBw {

                    }
                }
            }
            ColumnLayout {
                Layout.alignment: Qt.AlignTop
                Layout.margins: 8
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
                Layout.alignment: Qt.AlignTop
                Layout.margins: 8
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
                                color: CWA.Colors.shades500
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
            ColumnLayout {
                Layout.alignment: Qt.AlignTop
                Layout.margins: 8
                Label {
                    text: "Various"
                }
                Row {
                    spacing: 8
                    CWA.InlineIconButton {}
                    CWA.P2 {
                        text: "InlineIconButton"
                    }
                }
                Row {
                    spacing: 8
                    CWA.InlineIconButton {
                        size: "S"
                    }
                    CWA.P2 {
                        text: "InlineIconButton (size: S)"
                    }
                }
                Row {
                    spacing: 8
                    CWA.InlineTextPicButton {
                        text: "Ayran"
                    }
                    CWA.P2 {
                        text: "InlineTextPicButton"
                    }
                }
                Row {
                    spacing: 8
                    CWA.InlineTextPicButton {
                        size: "S"
                        text: "Ayran"
                    }
                    CWA.P2 {
                        text: "InlineTextPicButton (size: S)"
                    }
                }
            }
        }
        GridLayout {
            id: secondPage
            width: view.width
            height: view.height
            columns: 3
            ColumnLayout {
                Layout.alignment: Qt.AlignTop
                Layout.margins: 8
                Label {
                    text: "Panel"
                }
                CWM.PanelCard {

                }
                Label {
                    text: "Snackbar"
                }
                CWM.Snackbar {

                }
            }
        }
        GridLayout {
            id: thirdPage
            width: view.width
            height: view.height
            columns: 4
            ColumnLayout {
                Layout.alignment: Qt.AlignTop
                Layout.margins: 8
                Label {
                    text: "(organism)"
                }
            }
        }
    }
    PageIndicator {
        id: indicator
        count: view.count
        currentIndex: view.currentIndex
        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
