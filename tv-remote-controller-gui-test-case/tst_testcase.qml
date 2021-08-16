import QtQuick 2.0
import QtTest 1.0
Item {
    id:root
    TestCase {
        name: "test1"

        function test_available() {

            compare(1, 1);
        }
    }
}
