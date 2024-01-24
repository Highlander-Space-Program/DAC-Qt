import QtQuick
import QtQuick.Window
import Qt.labs.qmlmodels

Window {
    width: 1920
    height: 1080
    visible: true
    title: qsTr("Setup")
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

            property var inputPin: ["AI0", "AI1", "AI2", "AI3", "AI4", "AI5", "AI6", "AI7", "AI8", "AI9", "AI10", "AI11", "AI12", "AI13", "AI14", "AI15", "AI16", "AI17", "AI8"]
            property var pt: ["Chamber PT", "Ethanol Injector PT", "NOx Injector PT", "Ethanol Tank PT", "NOx Tank PT"]
            property var tc: ["Chamber TC 1", "Chamber TC 2", "Ethanol Tank TC", "NOx Tank TC"]
            property var lc: ["Thrust LC", "Ethanol Tank TC", "NOx Tank TC"]
            property var currentVoltage: [1234, 0, 5, 4.2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
            property var currentValue: [50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
            property var connectionStatus: ["N", "Y", "N", "N", "N", "N", "N", "N", "N", "N", "N", "N"]

            rows: [
                {
                    "Input pin": "Input pin",
                    "Assigned Input": "Assigned Input",
                    "Current Voltage": "Current Voltage",
                    "Current Value": "Current Value",
                    "Connection_Status": "Connection Status"
                },
                {
                    "Input pin": inputPin[0],
                    "Assigned Input": pt[0],
                    "Current Voltage": currentVoltage[0],
                    "Current Value": currentValue[0],
                    "Connection_Status": connectionStatus[0]
                },
                {
                    "Input pin": inputPin[1],
                    "Assigned Input": pt[1],
                    "Current Voltage": currentVolage[0],
                    "Current Value": currentValue[1],
                    "Connection_Status": connectionStatus[1]
                },
                {
                    "Input pin": inputPin[2],
                    "Assigned Input": pt[2],
                    "Current Voltage": currentVoltage[2],
                    "Current Value": currentValue[2],
                    "Connection_Status": connectionStatus[2]
                },
                {
                    "Input pin": inputPin[3],
                    "Assigned Input": pt[3],
                    "Current Voltage": currentVoltage[3],
                    "Current Value": currentValue[3],
                    "Connection_Status": connectionStatus[3]
                },
                {
                    "Input pin": inputPin[4],
                    "Assigned Input": pt[4],
                    "Current Voltage": currentVoltage[4],
                    "Current Value": currentValue[4],
                    "Connection_Status": connectionStatus[4]
                },
                {
                    "Input pin": inputPin[5],
                    "Assigned Input": tc[0],
                    "Current Voltage": currentVoltage[5],
                    "Current Value": currentValue[5],
                    "Connection_Status": connectionStatus[5]
                },
                {
                    "Input pin": inputPin[6],
                    "Assigned Input": tc[0],
                    "Current Voltage": currentVoltage[6],
                    "Current Value": currentValue[5],
                    "Connection_Status": connectionStatus[5]
                },
                {
                    "Input pin": inputPin[7],
                    "Assigned Input": tc[1],
                    "Current Voltage": currentVoltage[7],
                    "Current Value": currentValue[6],
                    "Connection_Status": connectionStatus[6]
                },
                {
                    "Input pin": inputPin[8],
                    "Assigned Input": tc[1],
                    "Current Voltage": currentVoltage[8],
                    "Current Value": currentValue[6],
                    "Connection_Status": connectionStatus[6]
                },
                {
                    "Input pin": inputPin[9],
                    "Assigned Input": tc[2],
                    "Current Voltage": currentVoltage[9],
                    "Current Value": currentValue[7],
                    "Connection_Status": connectionStatus[7]
                },

                {
                    "Input pin": inputPin[10],
                    "Assigned Input": tc[2],
                    "Current Voltage": currentVoltage[10],
                    "Current Value": currentValue[7],
                    "Connection_Status": connectionStatus[7]
                },
                {
                    "Input pin": inputPin[11],
                    "Assigned Input": tc[3],
                    "Current Voltage": currentVoltage[11],
                    "Current Value": currentValue[8],
                    "Connection_Status": connectionStatus[8]
                },

                {
                    "Input pin": inputPin[12],
                    "Assigned Input": tc[3],
                    "Current Voltage": currentVoltage[12],
                    "Current Value": currentValue[8],
                    "Connection_Status": connectionStatus[8]
                },
                {
                    "Input pin": inputPin[13],
                    "Assigned Input": lc[0],
                    "Current Voltage": currentVoltage[13],
                    "Current Value": currentValue[9],
                    "Connection_Status": connectionStatus[9]
                },
                {
                    "Input pin": inputPin[14],
                    "Assigned Input": lc[0],
                    "Current Voltage": currentVoltage[14],
                    "Current Value": currentValue[9],
                    "Connection_Status": connectionStatus[9]
                },
                {
                    "Input pin": inputPin[15],
                    "Assigned Input": lc[1],
                    "Current Voltage": currentVoltage[15],
                    "Current Value": currentValue[10],
                    "Connection_Status": connectionStatus[10]
                },





            ]
        }

        delegate: Rectangle {
            implicitWidth: Window.width / 5
            implicitHeight: 50
            border.width: 1
            border.color: "gray"
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
