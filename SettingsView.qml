import QtCore
import QtQuick
import QtQuick.Controls

import '.'
import './components/settings/'

Item {
  id: root

  property QSettings settings

  ObjectModel {
    id: input_model

    SettingsTextInput {
      parent: listview
      key: "identifier"
      group: "labjack"
      name: "Identifier"
      value: settings.value("labjack/identifier")
    }
    SettingsTextInput {
      parent: listview
      key: "device_type"
      group: "labjack"
      name: "Device Type"
      value: settings.value("labjack/device_type")
    }
    SettingsTextInput {
      parent: listview
      key: "connection_type"
      group: "labjack"
      name: "Connection Type"
      value: settings.value("labjack/connection_type")
    }
    SettingsComboInput {
      parent: listview
      name: "Protocol"
      model: ["http", "https"]
      key: "protocol"
      group: "influx"
      defaultValue: settings.value("influx/protocol")
    }
    SettingsTextInput {
      parent: listview
      name: "Address"
      key: "address"
      group: "influx"
      value: settings.value("influx/address")
    }
    SettingsTextInput {
      parent: listview
      name: "Port"
      key: "port"
      group: "influx"
      value: settings.value("influx/port")
    }
    SettingsTextInput {
      parent: listview
      name: "Bucket"
      key: "db"
      group: "influx"
      value: settings.value("influx/db")
    }
    SettingsTextInput {
      parent: listview
      name: "Measurement"
      key: "measurement"
      group: "influx"
      value: settings.value("influx/measurement")
    }
    SettingsTextInput {
      parent: listview
      name: "Token"
      key: "token"
      group: "influx"
      value: settings.value("influx/token")
    }
  }

  Column {
    anchors.fill: parent

    ListView {
      id: listview

      anchors.left: parent.left
      anchors.right: parent.right
      implicitHeight: 415

      model: input_model
      section.property: "group"
      section.delegate: SettingsDivider { }
    }

    SettingsDivider { }

    Row {
      anchors.horizontalCenter: parent.horizontalCenter

      Button {
        text: "Save"
        onClicked: {
          for (let i = 0; i < input_model.count; i++) {
            let item = input_model.get(i);
            settings.setValue(item.group+'/'+item.key, item.value);
          }
        }
      }
/* TODO
      Button {
        text: "Reset"
      }
*/
    }
  }
}
