import QtQuick
import QtQuick.Window
import Qt.labs.qmlmodels

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    TableView {
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        model: TableModel {
            TableModelColumn { display: "Input pin" }
            TableModelColumn { display: "Assigned Input" }
            TableModelColumn { display: "Current Voltage" }
            TableModelColumn { display: "Current Value" }
            TableModelColumn { display: "Connection Status" }

            rows: [
                {
                    "Input pin": "Input pin",
                    "Assigned Input": "Assigned Input",
                    "Current Voltage": pt1Voltage1,
                    "Current Value": "Current Value",
                    "Connection Status": "Connection Status"
                },
                {
                    "Input pin": "AI0",
                    "Assigned Input": "PT1 HIGH",
                    "Current Voltage": "0.0V",
                    "Current Value": "0000",
                    "Connection Status": "N"
                },
                {
                    "Input pin": "AI1",
                    "Assigned Input": "PT1 LOW",
                    "Current Voltage": "3.4V",
                    "Current Value": "1234",
                    "Connection Status": "Y"
                },

            ]
        }

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            border.width: 1

            Text {
                text: display
                anchors.centerIn: parent
            }
        }
    }
}
