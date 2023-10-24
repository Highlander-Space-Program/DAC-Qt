import QtQuick
import QtQuick.Window
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    StackLayout {
      id: root
      anchors.fill: parent

      Visualization { }
      Navigation { }
      Settings { }
      Pinout { }
    }
}


