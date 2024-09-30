import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
  id: root

  anchors.left: parent.left
  anchors.right: parent.right
  implicitHeight: 40

  property string key
  property string group

  property string defaultValue
  property alias value: input.currentText
  property alias model: input.model
  property alias name: display_name.text
  property alias input: input

  Component.onCompleted: {
    if (defaultValue) {
      input.currentIndex = input.indexOfValue(defaultValue);
    }
  }

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