import QtQuick
import QtQuick.Controls
import Qt.labs.qmlmodels

Item {
   // anchors.fill parent
    //width: 1500
   // height: 800
    width: parent.width
    height: parent.height

    Rectangle {
        width: parent.width
        height: parent.height
        color: "black"

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
                property var voltInput: [0.00, 3.40, 2.3]
                property var valueRead: [000, 314159, 27182]


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
                            "Current Voltage": voltInput[0] +"V",
                            "Current Value": valueRead[0],
                            "Connection_Status": "N"
                        },
                    {
                        "Input pin": rowInput[1],
                        "Assigned Input": "PT1 LOW",
                        "Current Voltage": voltInput[1] + "V",
                        "Current Value": valueRead[1],
                        "Connection_Status": "Y"
                    },
                ]
            }

            delegate: Rectangle {
                implicitWidth: parent.width / 5
                implicitHeight: 50
                border.width: 1
                border.color: "yellow"
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
}
