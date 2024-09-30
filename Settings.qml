import QtQuick
import QtQuick.Controls

Item {
  id: root

  Column {
    anchors.fill: parent

    SettingsSectionLabJack { id: labjack }

    SettingsDivider { }

    SettingsSectionInflux { id: influx }

    SettingsDivider { }

    Row {
      Button {
        text: "Save"
        onClicked: {
          console.log(JSON.stringify({
            'labjack': labjack.to_obj(),
            'influx': influx.to_obj()
          }));
        }
      }
      Button {
        text: "Reset"
      }
    }

  }
}
