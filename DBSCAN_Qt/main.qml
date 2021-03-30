import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    color: "#e8e8e8"
    title: qsTr("DBSCAN")

    property bool isShowRegion: showRegionCheckBox.checked
    property int observationSize: 10
    property int _MinEpsilon_: 10
    property int _MaxEpsilon_: 100

    property int epsilon: _MinEpsilon_ + _MaxEpsilon_ * epsilonSlider.value

    Text {
        id: element
        x: 479
        y: 49
        text: qsTr("Epsilon: " + epsilon)
        font.pixelSize: 12
    }


    Rectangle {
        x: 16
        y: 30
        width: 457
        height: 436
        color: "#000000"
        Text {
            id: txtTitle
            x: 0
            y: -16
            text: qsTr("Observations")
            font.pixelSize: 12
        }
        Item {
            id: observationGroup
            anchors.fill: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log("Hello" + (mouseX- observationSize/2) +" - " + (mouseY- observationSize/2))
                addNewObservation(mouseX - observationSize/2, mouseY-observationSize/2)
                //appController.addNewObservation(observationGroup, mouseX - observationSize/2, mouseY-observationSize/2);
            }
        }

    }

    Button {
        x: 482
        y: 220
        width: 142
        height: 26
        text: qsTr("START")
        onClicked: {
            showRegionCheckBox.checked = false
            appController.getAllObservations(observationGroup, epsilon, parseInt(txtMinPoint.text));
        }
    }

    Button {
        x: 482
        y: 250
        width: 142
        height: 26
        text: qsTr("RESET")
        onClicked: {
            showRegionCheckBox.checked = true
            for(var i = observationGroup.children.length; i > 0 ; i--) {
                observationGroup.children[i-1].label = 0
            }
            appController.clear();
        }
    }

    Button {
        id: btClear
        x: 510
        y: 426
        text: qsTr("CLEAR")
        onClicked: {
            //            console.log("count: " + observationGroup.children[0].x + observationSize/2);
            console.log(observationGroup.children.length)
            for(var i = observationGroup.children.length; i > 0 ; i--) {
                observationGroup.children[i-1].destroy()
            }
            appController.clear();
        }
    }



    Observation {
        id: sampleObservation
        x: 582
        y: 49
        label: 1
        isShowRegion: true
    }

    Slider {
        id: epsilonSlider
        x: 482
        y: 69
        width: 142
        height: 40
        font.pointSize: 40
        value: 0.35

    }

    Text {
        id: element1
        x: 482
        y: 141
        text: qsTr("Min Points:")
        font.pixelSize: 12
    }

    TextInput {
        id: txtMinPoint
        x: 550
        y: 139
        width: 80
        height: 20
        text: qsTr("3")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }

    CheckBox {
        id: showRegionCheckBox
        x: 482
        y: 165
        text: qsTr("Show Region")
        checkState: Qt.Checked
    }

    Text {
        id: element2
        x: 501
        y: 315
        text: qsTr("Number Of Cluster: " + appController.numberOfCluster)
        font.pixelSize: 12
    }

    Text {
        id: element3
        x: 501
        y: 348
        text: qsTr("Number Of Outliers: " + appController.numberOfOutliers)
        font.pixelSize: 12
    }


    function addNewObservation(posX, posY){
        var component = Qt.createComponent("Observation.qml");
        var newObject = component.createObject(observationGroup, {x: posX, y: posY});

        if (newObject === null) {
            console.log("Error creating object");
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/
