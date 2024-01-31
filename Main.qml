import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

ApplicationWindow {
  id: widnow
  width: 1920
  height: 1080
  visible: true
  title: qsTr("Hello World")

  GridLayout {
    id: root
    anchors.fill: parent

    Navigation { stack: content }

    StackLayout {
      id: content

      Layout.fillWidth: true
      Layout.fillHeight: true

      Visualization { }
      Settings { }
    }
  }
}


