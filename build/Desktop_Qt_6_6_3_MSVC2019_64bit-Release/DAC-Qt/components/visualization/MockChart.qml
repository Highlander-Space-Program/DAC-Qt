import QtQuick
import QtCharts

Item {
  id: root

  ChartView {
    id: thrust_graph
    anchors.fill: parent

    title: "Thrust"
    legend.visible: false
    theme: ChartView.ChartThemeDark

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
}
