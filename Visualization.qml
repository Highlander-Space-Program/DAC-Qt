import QtQuick
import QtQuick.Layouts
import QtCharts

Item {
  id: root
  GridLayout {
    id: graphs
    anchors.fill: parent
    columns: 1
    rows: 2

    ChartView {
      id: thrust_graph
      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.preferredHeight: 75

      title: "Thrust"

      DateTimeAxis {
        id: axis_x
        format: "hh:mm:ss.zzz"
      }
      LineSeries {
        id: series
        axisX: axis_x

        XYPoint {
          x: 1699140289; y: 114.276
        }
        XYPoint {
          x: 1699140290; y: 114.403
        }
        XYPoint {
          x: 1699140291; y: 114.403
        }
        XYPoint {
          x: 1699140292; y: 114.403
        }
        XYPoint {
          x: 1699140293; y: 114.655
        }
        XYPoint {
          x: 1699140294; y: 114.15
        }
        XYPoint {
          x: 1699140295; y: 114.15
        }
        XYPoint {
          x: 1699140296; y: 114.276
        }
        XYPoint {
          x: 1699140297; y: 114.276
        }
        XYPoint {
          x: 1699140298; y: 114.403
        }
        XYPoint {
          x: 1699140299; y: 114.15
        }
        XYPoint {
          x: 1699140300; y: 114.529
        }
        XYPoint {
          x: 1699140301; y: 114.403
        }
        XYPoint {
          x: 1699140302; y: 114.403
        }
        XYPoint {
          x: 1699140303; y: 113.898
        }
      }
    }

    Item {
      id: values
      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.row: 2
      Layout.preferredHeight: 25
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
