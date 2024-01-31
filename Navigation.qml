import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Drawer {
  id: root

  required property StackLayout stack

  width: 0.33 * parent.width
  height: parent.height
  modal: true
  dragMargin: 16

  ColumnLayout {
    id: layout

    anchors.fill: parent

    NavButton {
      stack: root.stack
      text: "Visualization"
      index: 0
    }
    NavButton {
      stack: root.stack
      text: "Settings"
      index: 1
    }
  }
}
