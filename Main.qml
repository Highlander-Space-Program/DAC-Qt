import QtQuick
import QtQuick.Window
import QtQuick.Layouts

Window {
    width: 1920
    height: 1080
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


