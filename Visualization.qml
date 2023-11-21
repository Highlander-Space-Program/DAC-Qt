import QtQuick
import QtQuick.Layouts

Item {
  id: root
  GridLayout {
    id: graphs
    anchors.fill: parent
    columns: 1
    rows: 2

    Item {
      id: charts
      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.preferredHeight: 85

      GridLayout {
        anchors.fill: parent
        columns: 3

        MockChart {
          Layout.fillWidth: true
          Layout.fillHeight: true
        }
        MockChart {
          Layout.fillWidth: true
          Layout.fillHeight: true
        }
        MockChart {
          Layout.fillWidth: true
          Layout.fillHeight: true
        }
        MockChart {
          Layout.fillWidth: true
          Layout.fillHeight: true
        }
        MockChart {
          Layout.fillWidth: true
          Layout.fillHeight: true
        }

      }
    }

    Item {
      id: values
      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.row: 2
      Layout.preferredHeight: 15
      Layout.margins: 5

      RowLayout {
        anchors.fill: parent

        Text { text: "Fuel Pressure: 800 PSI" }
        Text { text: "Fuel Temperature: 33 C" }
        Text { text: "Oxidizer Pressure: 800 PSI" }
        Text { text: "Oxidizer Temperature: 35 C" }
      }
    }
  }
}
