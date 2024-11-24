import '.'

import QtQuick
import QtCharts 2.3

Item {
  id: root

  required property Subscriber subscriber
  property alias title: view.title

  Connections {
    target: subscriber
    function onStartChanged(start) { axis_x.max = start; }
    function onEndChanged(end) { axis_x.min = end; }
  }

  ChartView {
    id: view
    anchors.fill: parent

    legend.visible: false
    theme: ChartView.ChartThemeDark

    DateTimeAxis {
      id: axis_x
      min: subscriber.end
      max: subscriber.start
    }
    ValueAxis {
        id: axis_y
        min: 1
        max: 1000
        labelFormat: "%.2f"
    }

    LineSeries {
      id: line_series
      axisX: axis_x
      axisY: axis_y
      useOpenGL: true
    }

    Timer {
      id: refreshTimer
      running: true
      repeat: true
      interval: 1 / 60 * 1000
      onTriggered: {
        subscriber.update(view.series(0));
      }
    }
  }
}
