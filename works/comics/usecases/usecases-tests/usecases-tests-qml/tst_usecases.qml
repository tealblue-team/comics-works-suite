import QtQml 2.2
import QtTest 1.0
import comicsworks.entities 1.0 as E
import comicsworks.usecases 1.0
import "."

TestCase {
    name: "usecases"

    CreateGrid {}

    function cleanup() {
        E.World.entities = null;
    }

    QtObject {
        id: when
        function i_create_a_grid_with_p1_rows_and_p2_columns(rows, columns) {
            UActions.create_grid(rows, columns);
        }
    }

    QtObject {
        id: then
        function i_should_get_a_grid_with_p1_x_p2_panels(rows, columns) {
            compare(E.World.grid.rows, rows);
            compare(E.World.grid.columns, columns);
        }
    }

    function test_create_grid__success_data() {
        return [
                    {tag:"default", rows:"",    columns:"",     gridRows:1,     gridColumns:1},
                    {tag:"1x1",     rows:1,     columns:1,      gridRows:1,     gridColumns:1},
                    {tag:"2x3",     rows:2,     columns:3,      gridRows:2,     gridColumns:3}
                ]
    }

    function test_create_grid__success(data) {
        when.i_create_a_grid_with_p1_rows_and_p2_columns(data.rows, data.columns);
        then.i_should_get_a_grid_with_p1_x_p2_panels(data.gridRows, data.gridColumns);
    }
}
