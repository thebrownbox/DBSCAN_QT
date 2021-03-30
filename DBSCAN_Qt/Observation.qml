import QtQuick 2.0
import QtQuick.Controls 2.0
Rectangle {
    property int size: mainWindow.observationSize
    property int border_size: size/10
    property int epsilon: mainWindow.epsilon
    property bool isShowRegion: mainWindow.isShowRegion
    property int label: 0
    property variant colors: ['white', 'red', 'orange', 'yellow', 'green', 'blue', 'purple', 'brown' ]
    width: size
    height: size
    radius: width/2
//    color: "#f5f5f5"
    color: label < 0 ? "gray" : colors[label]
    border.width: border_size
    border.color: "black"

    Rectangle{
        id: regionCircle
        x: -(height/2) + size/2
        y: -(width/2) + size/2
        height: epsilon * 2
        width: epsilon * 2
        color: parent.color
        opacity: 0.35
        radius: width/2
        border.width: 1
        border.color: parent.color
        visible: label == 0 ? isShowRegion : true
    }


    NumberAnimation {
        id: anim1
        target: regionCircle
        property: "height"
        from: 0
        to: epsilon * 2
        duration: 200
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        id: anim2
        target: regionCircle
        property: "width"
        from: 0
        to: epsilon * 2
        duration: 200
        easing.type: Easing.InOutQuad
    }



    onLabelChanged: {
        if(label > 0){
            anim1.start()
            anim2.start()
        }
    }
}
