import QtQuick 2.9
import QtQuick.Layouts 1.3
import "."

Item {
    property alias rows: lout.rows
    property alias columns: lout.columns

    GridLayout {
        id: lout
        rows: 1
        columns: 1
    }
}
