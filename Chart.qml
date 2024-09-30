import QtQuick
import QtCharts

Item {
  id: root

  required property Subscriber subscriber
  property alias title: chart.title


  ChartView {
    id: chart
    anchors.fill: parent

    legend.visible: false
    theme: ChartView.ChartThemeDark

    ValueAxis {
      id: axis_x
    }
    ValueAxis {
      id: axis_y
    }
    LineSeries {
      id: line_series
      name: "pressure"
      axisX: axis_x
      axisY: axis_y
    }

    Timer {
      id: refreshTimer
      running: true
      repeat: true
      interval: 1 / 60 * 1000
      onTriggered: {
        subscriber.update(chart.series(0));
      }
    }

  }
}
