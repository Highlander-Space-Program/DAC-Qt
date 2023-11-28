import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {

    GridView {
        id: myGridView
        cellWidth: parent.width / 3
        cellHeight: 50
        anchors.fill: parent

        model: ListModel {
            ListElement { name: "Visualization" }
            ListElement { name: "Setup" }
            ListElement { name: "Settings" }
        }

        delegate: Button {
            id: myButton
            text: name
            width: myGridView.cellWidth - 10
            height: myGridView.cellHeight
            background: Rectangle {
                color: "black"
            }
            contentItem: Text {
                text: myButton.text
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 16
            }

            onClicked: {
                load_page(text)
            }
        }
    }
}
