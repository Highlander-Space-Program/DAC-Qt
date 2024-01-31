import QtQuick
import QtQuick.Window
import QtQuick.Layouts

Window {
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


