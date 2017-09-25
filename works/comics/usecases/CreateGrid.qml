import QtQuick 2.2
import comicsworks.entities 1.0 as E
import "."

Connections {
    property Component grid: Component {
        id: grid
        E.Grid {}
    }
    target: UActions
    onCreate_grid: {
        if (!rows) rows = 1;
        if (!columns) columns = 1;
        E.World.grid = grid.createObject(E.World,{rows:rows,columns:columns});
    }
}
