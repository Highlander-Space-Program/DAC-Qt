import QtQuick
import QtQuick.Window
import Qt.labs.qmlmodels

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Setup")

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
            TableModelColumn { display: "Connection_Status" }

            property var rowInput: ["AI0", "AI1", "AI2"]

            rows: [
                {
                    "Input pin": "Input pin",
                    "Assigned Input": "Assigned Input",
                    "Current Voltage": "Current Voltage",
                    "Current Value": "Current Value",
                    "Connection_Status": "Connection Status"
                },
                {
                    "Input pin": rowInput[0],
                    "Assigned Input": "PT1 HIGH",
                    "Current Voltage": "0.0V",
                    "Current Value": "0000",
                    "Connection_Status": "N"
                },
                {
                    "Input pin": rowInput[1],
                    "Assigned Input": "PT1 LOW",
                    "Current Voltage": "3.4V",
                    "Current Value": "1234",
                    "Connection_Status": "Y"
                },

            ]
        }

        delegate: Rectangle {
            implicitWidth: 100
            implicitHeight: 50
            border.width: 1
            property string defaultColor: "black"
            property string disconnectedColor: "Red"
            property string connectedColor: "Green"

            Text {
                color: "yellow"
                text: (display == "Y" || display == "N") ? "" : display
                anchors.centerIn: parent
            }

            color: (display == "Y") ? connectedColor : (display == "N") ? disconnectedColor : defaultColor
        }
    }
}
