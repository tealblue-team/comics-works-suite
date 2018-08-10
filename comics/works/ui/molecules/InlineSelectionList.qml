import QtQuick 2.0
import QtQuick.Controls 2.3
import "../atoms" as CWA

ListView {
    id: root
    signal itemClicked(string name)
    width: 80
    clip: true
    height: (count<5 ? count*24 : 4*24) + 8
    currentIndex: 0
    delegate: ItemDelegate {
        padding: 4
        text: typeof(modelData)=="undefined" ? modelData.name : model.name
        font.pixelSize: CWA.Typo.p2
        onClicked: itemClicked(model.name)
        Keys.onReturnPressed: itemClicked(model.name)
        width: 80
        height: 24
        Keys.onTabPressed: currentIndex < count-1 ? currentIndex += 1 : currentIndex=0
        Keys.onBacktabPressed: currentIndex > 0 ? currentIndex -= 1 : currentIndex=count-1
        background: Rectangle {
            color: parent.activeFocus ? CWA.Colors.primary500 : CWA.Colors.shades200
        }
    }
}
