import QtQuick
import QtCharts

Item {
  id: root

    ChartView {
      id: chart
      anchors.fill: parent
      title: "Pressure"
      antialiasing: true

      ValueAxis {
        id: axisY
        min: -5
        max: 1000
      }
      DateTimeAxis {
        id: axisX
        format: "hh:mm:ss.zzz"
        min: visualizationContext.minX
        max: visualizationContext.maxX
      }
      LineSeries {
        id: series
        useOpenGL: true
        axisX: axisX
        axisY: axisY
      }
    }

    Text {
      text: visualizationContext.currentValue
    }

  Timer {
    id: refreshTimer
    interval: 1/60 * 1000
    running: true
    repeat: true
    onTriggered: {
       visualizationContext.update(series);
    }
  }
}
