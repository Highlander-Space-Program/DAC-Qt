import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 1920
    height: 1080
    visible: true
    title: qsTr("QT Application")
    header: ToolBar{
        RowLayout {
            anchors.fill: parent
            ToolButton{
                text: qsTr('<')
                onClicked: myStackView.pop()
            }
            Label {
                text: "Marlon Stackview"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AllignHCenter
                verticalAlignment: Qt.AllignVCenter
                Layout.fillWidth: true
            }
        }
    }
//Stackview to switch over pages so the main page is kinda like the page where you chose where you want to go
    StackView {
      id: myStackView
      anchors{
          left: parent.left
          right: parent.right
          bottom: parent.bottom
          top: header.bottom
      }

      initialItem: navigation
    }
    Component {
        id:navigation
        Navigation{}
    }
    Component {
        id:visualization
        Visualization{}
    }
    Component {
        id:settings
        Settings{}
    }
    Component {
        id:setup
        Setup{}
    }
    function load_page(page){
        switch(page){

        case 'Visualization':

            myStackView.push(visualization)
            break;
        case 'Setup':

            myStackView.push(setup)
            break;
        case 'Settings':
            myStackView.push(settings)
            break;
        }
    }


}


