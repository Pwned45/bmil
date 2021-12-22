import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.3
//![0]
ListView {
    id: keysView
//    width: 400
//    height: 1200
    anchors.fill: parent
    clip: false
    implicitHeight: height

    currentIndex: -1
    model: biometricModel
    spacing: 1
    orientation: Qt.Horizontal
    Component.onCompleted: {
                forceActiveFocus(); //необходимо для обработки нажатия клавиш
                console.log("listView activeFocus: "+activeFocus)
            }

//    Keys.onPressed: {
////        if (event.key == Qt.Key_Left) {
////            console.log("move left");
////            event.accepted = true;
////        }
//        biometricModel.appendRow(event.key,0)
//        console.log(event.key)
//        //console.log()
//    }
    Keys.onPressed: {
        if (Qt.Key_Backspace !== event.key) {
        if (Qt.Key_Shift !== event.key && Qt.Key_Alt !== event.key)
        biometricModel.appendRow(event.text,0)
        } else {
            biometricModel.removeLast()
        }

        console.log(event.text)
    }
    Keys.onReleased: {
        if (Qt.Key_Backspace !== event.key) {
        if (Qt.Key_Shift !== event.key && Qt.Key_Alt !== event.key)
        biometricModel.appendRow(event.text,1)
        } else {

        }

        console.log("released " + event.text)
    }

//    Keys.onReleased: {
//        biometricModel.appendRow(event.key,1)
//        console.log("released " + event.key)
//    }

    delegate: Rectangle {
        height: 80
        width: 16

        radius: 5

        RowLayout {
            id: theDelegate

            anchors {
                fill : parent
                margins: 5
            }
            Text {
                Layout.fillWidth: true
                Layout.fillHeight: true

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font {
                    pixelSize: 22
                }

                //elide: Text.ElideRight

                color: "red"

                text: key
            }
        }
    }
    ScrollView {
        anchors.fill: parent
        anchors.margins: {
            topMargin:45
        }

        clip: true
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            contentHeight: 2300
            contentWidth: 800
    ColumnLayout {
        Connections {
            target: biometricModel

            onAddToGisrogramm: {
                enterGist_ID.append(a_index, a_value)
                console.log(a_index);
                console.log(a_value);
            }
            onAddToGisrogramm2: {
                enterStaticGist_ID.append(a_index, a_value)
                console.log(a_index);
                console.log(a_value);
            }
            onRemoveFromGistogramm: {
                enterGist_ID.remove(a_index)
                enterStaticGist_ID.remove(a_index)
                console.log(a_index);
            }
            onAddToAmplitudeFunction: {
                enterGist3_ID.append(a_index, a_value)
                console.log(a_index)
            }

        }

    Text {
        text: biometricModel.complexity
        font {
            pixelSize: 22
        }
    }
    ChartView {

        antialiasing: false
        Layout.fillWidth: true
        Layout.fillHeight: false
        Layout.preferredHeight: 400
        Layout.preferredWidth:800

        LineSeries {
            axisY: ValueAxis {
                min: 0
                max: 800
//                labelFormat: "Hold time"
                titleText: "Hold time"
            }
            axisX: ValueAxis {
                min: 0
                max: 10
                labelFormat: "%.0f"
                tickCount: 10
                titleText: "Number of symbol"
            }

            id: enterGist_ID
            name: "Dynamics"
        }
    }
    ChartView {

        antialiasing: false
        Layout.fillWidth: true
        Layout.fillHeight: false
        Layout.preferredHeight: 400
        Layout.preferredWidth:400

        LineSeries {
            axisY: ValueAxis {
                min: 0
                max: 2
//                labelFormat: "Hold time"
                titleText: "Interval"
            }
            axisX: ValueAxis {
                min: 0
                max: 10
                labelFormat: "%.0f"
                tickCount: 10
                titleText: "Number of symbol"                
            }
            color: "red"
            id: enterStaticGist_ID
            name: "Intervals"
        }
    }

    Label {
        text: "Press time statistics"
        font.pixelSize: 32
        font.italic: true
    }
    Text {
        text: "Dispersion: " + biometricModel.dispersionPressTime + "ms"
        font {
            pixelSize: 22
        }
    }
    Text {
        text:"Expected Value: "+ biometricModel.expectedPressTime+ "ms"
        font {
            pixelSize: 22
        }
    }
    Text {
        text:"Press time sum: " + biometricModel.pressTimeSum + "ms"
        font {
            pixelSize: 22
        }
    }
    Label {
        text: "Intervals statistics"
        font.pixelSize: 32
        font.italic: true
    }
    Text {
        text:"Dispersion: " + biometricModel.dispersionIntervals  + "ms"
        font {
            pixelSize: 22
        }
    }
    Text {
        text:"Expected Value: "+ biometricModel.expectedIntervals+ "ms"
        font {
            pixelSize: 22
        }
    }
    Label {
        text: "Superpositions"
        font.pixelSize: 32
        font.italic: true
    }
    Text {
        text: "Galop overlay: " + biometricModel.gallopSuperpos+ "ms"
        font {
            pixelSize: 22
        }
    }
    Text {
        text: "Absorption: " + biometricModel.absorption+ "ms"
        font {
            pixelSize: 22
        }
    }
    Button {
        text: "Calculate Vector"
        onClicked: {
            biometricModel.calculateVector()
        }
        font {
            pixelSize: 22
        }
    }
    Text {
        text: "Biom Vector: " + biometricModel.vector
        font {
            pixelSize: 22
        }
    }
    Rectangle {
            color: "steelblue"
            width: 130
            height: 30
    TextEdit {
        id: userName_ID
        text: "User Name"
        font {
            pixelSize: 22
        }
        color: "white"
    }
    }

//    Button {
//        text: "Save User"
//        onClicked: {
//            biometricModel.saveCurrWithName(userName_ID.text)
//        }
//        font {
//            pixelSize: 22
//        }
//    }
//    Button {
//        text: "Show Users"
//        onClicked: {
//            biometricModel.saveCurrWithName(userName_ID.text)
//        }
//        font {
//            pixelSize: 22
//        }
//    }

    Button {
        text: "Register"
        onClicked: {
            biometricModel.registerClick(userName_ID.text);
        }
        font {
            pixelSize: 22
        }
    }
    Button {
        text: "Autorization"
        onClicked: {
            biometricModel.autorizationClick(userName_ID.text);
        }
        font {
            pixelSize: 22
        }
    }
    ChartView {

        antialiasing: false
        Layout.fillWidth: true
        Layout.fillHeight: false
        Layout.preferredHeight: 400
        Layout.preferredWidth:800

        LineSeries {
            axisY: ValueAxis {
                min: 0
                max: 15
                //                labelFormat: "Hold time"
                tickCount: 3
                titleText: "Amplitude"
            }
            axisX: ValueAxis {
                min: biometricModel.getMinTime() + 2300
                max: biometricModel.getMinTime() + 10000
                labelFormat: "%.0f"
                tickCount: 10
                titleText: "Key Times Value"
            }

            id: enterGist3_ID
            name: "FunctionValue"
            color: "black"
        }
    }
    Button {
        text: "Show Grafic"
        onClicked: {
            biometricModel.calculateGraphAmplitude()
        }
        font {
            pixelSize: 22
        }
    }
    }

}
}

//![0]
