import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    StackLayout {
      id: root
      anchors.fill: parent

      signal closeSettings
      signal openSettings

      onOpenSettings: currentIndex = 1;
      onCloseSettings: currentIndex = 0;

      Item {
        GridLayout {
          id: visualization
          columns: 1
          rows: 1

          anchors.fill: parent;

          Button {
            Layout.alignment: Qt.AlignHCenter
            text: "Settings"

            onClicked: ()=> {
                           console.log("Open settings...");
                           root.openSettings();
                       }
          }
        }
      }

      Item {
        GridLayout {
          id: settings
          anchors.fill: parent
          columns: 2

          Button {
            Layout.alignment: Qt.AlignCenter
            text: "Save"

            signal save

            onClicked: ()=> {
                           save();
                           root.closeSettings();
                       }
            onSave: ()=> console.log("Saved");
          }
        }
      }
    }
}


