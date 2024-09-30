import QtQuick
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

    Rectangle {
      id: input_container
      Layout.margins: 8
      Layout.fillWidth: true
      Layout.preferredHeight: input.height
      color: "dimgray"

      Flickable {
        anchors.fill: parent
        clip: true

        TextInput {
          id: input
          anchors.verticalCenter: parent.verticalCenter
          bottomPadding: 4
          leftPadding: 8
          rightPadding: 8
          topPadding: 4
          width: parent.width
          color: "white"
        }
      }
    }
  }
}