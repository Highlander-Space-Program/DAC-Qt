import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
  id: root

  anchors.left: parent.left
  anchors.right: parent.right
  implicitHeight: 40

  property string key
  property alias name: display_name.text
  property alias input: input

  RowLayout {
    anchors.fill: parent

    Text {
      id: display_name
      Layout.margins: 8
      Layout.preferredWidth: 120
      text: "Address"
      color: "white"
    }

    Item {
      Layout.fillWidth: true
      Layout.fillHeight: true

      ComboBox {
        id: input
        anchors.left: parent.left
      }
    }
  }
}