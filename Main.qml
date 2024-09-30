import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

ApplicationWindow {

  id: widnow
  width: 1920
  height: 1080
  visible: true
  title: qsTr("Highlander Space Program DAQ")

  Navigation { stack: content }

  GridLayout {
    id: root
    anchors.fill: parent
    columns: 2
    rows: 2

    ColumnLayout {
      id: sidebar

      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.column: 1
      Layout.row: 1
      Layout.preferredWidth: 12

      Rectangle {
        color: "transparent"
        border.color: "black"
        border.width: 1
        Layout.fillWidth: true
        Layout.fillHeight: true
        ListView {
          anchors.fill: parent
          anchors.margins: 8
          model:
            ListModel {
              ListElement {
                message: "InfluxDB error: "
              }
              ListElement {
                message: "LabJack error: "
              }
              ListElement {
                message: "Error connecting to database"
              }
              ListElement {
                message: "Error connecting to database"
              }
            }
          delegate:
            Rectangle {
              width: ListView.view.width
              height: 50
              color: hoverHandler.hovered ? "slategray" : "transparent"
              Text {
                anchors.fill: parent
                wrapMode: Text.Wrap
                verticalAlignment: Qt.AlignVCenter
                padding: 4
                text: message
                color: "white"
              }
              HoverHandler { id: hoverHandler }
            }
        }
      }

      Button {
        id: settings
        Layout.alignment: Qt.AlignBottom
        Layout.fillWidth: true
        text: context.test
      }
      Button {
        id: record
        Layout.alignment: Qt.AlignBottom
        Layout.fillWidth: true
        Layout.preferredHeight: 50
        text: "Record"
      }
    }

    StackLayout {
      id: content

      Layout.fillWidth: true
      Layout.fillHeight: true
      Layout.column: 0
      Layout.row: 1
      Layout.preferredWidth: 88

      Item {
        SettingsView {
          settings: context.settings
          anchors.fill: parent
          anchors.leftMargin: 64
          anchors.rightMargin: 64
        }
      }

      Visualization { }
    }
  }
}


