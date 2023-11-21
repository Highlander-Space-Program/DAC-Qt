import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
Item {
    GridView{
        id: myGridView
        cellWidth: parent.width /3
        cellHeight: 10
        anchors.fill: parent
        model: ListModel {
            ListElement{
                name: "Visualization"
            }
            ListElement{
                name:"Setup"
            }
            ListElement{
                name: "Settings"
            }
        }
        delegate: Button{
            id: myButton
            text: name
            onClicked: {
                load_page(text)
            }
        }
    }


}
