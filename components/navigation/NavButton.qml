import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
  id: root

  property alias text: button.text
  required property int index
  required property StackLayout stack

  Layout.fillHeight: true
  Layout.fillWidth: true

    Button {
      id: button

      anchors.fill:parent
      flat: true

      onClicked: () => { stack.currentIndex = index; }
    }
}
