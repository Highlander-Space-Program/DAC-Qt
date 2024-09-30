import QtQuick
import QtQuick.Controls

Item {
  id: root

  anchors.left: parent.left
  anchors.right: parent.right
  implicitHeight: 250

  Column {
    anchors.fill: parent

    ObjectModel {
      id: input_model

      SettingsComboInput {
        id: protocol
        parent: view
        key: "protocol"
        name: "Protocol"
        input.model: ["http", "https"]
      }
      SettingsTextInput {
        id: address
        parent: view
        key: "address"
        name: "Address"
      }
      SettingsTextInput {
        id: port
        parent: view
        key: "port"
        name: "Port"
      }
      SettingsTextInput {
        id: db
        parent: view
        key: "db"
        name: "Bucket"
      }
      SettingsTextInput {
        id: measurement
        parent: view
        key: "measurement"
        name: "Measurement"
      }
      SettingsTextInput {
        id: token
        parent: view
        key: "token"
        name: "Token"
      }
    }

    ListView {
      id: view
      anchors.fill: parent
      model: input_model
    }
  }

  function to_obj() {
    let obj = { };
    for (let i = 0; i < input_model.count; i++) {
      let item = input_model.get(i);
      obj[item.key] = item.input.text;
    }
    return obj;
  }

}