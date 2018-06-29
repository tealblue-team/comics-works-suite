import QtQuick 2.0
import QtQuick.Controls 2.2
import "../atoms" as CWA

Button {
    id: button
    font.pixelSize: CWA.Typo.p2
    background: Rectangle {
        radius: 4
        color: pressed ? CWA.Colors.shades300 : CWA.Colors.shades100
    }
}