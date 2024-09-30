import QtQuick

Item {
  id: root

  anchors.left: parent.left
  anchors.right: parent.right
  implicitHeight: 125

  Column {
    id: inputs
    anchors.fill: parent

    SettingsTextInput {
      id: identifier_input
      key: "identifier"
      name: "Identifier"
    }
    SettingsTextInput {
      id: device_type_input
      key: "device_type"
      name: "Device Type"
    }
    SettingsTextInput {
      id: connection_type_input
      key: "connection_type"
      name: "Connection Type"
    }
  }

  function to_obj() {
    let obj = { };
    for (let child of inputs.children) {
      obj[child.key] = child.input.text;
    }
    return obj;
  }

}