import QtQuick

Item {
  id: root

  anchors.left: parent.left
  anchors.right: parent.right
  height: 16

  property alias divider: divider

  Rectangle {
    id: divider

    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter

    implicitWidth: parent.width/2
    implicitHeight: 1

    color: "dimgray"
  }
}