import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Window {
    visible: true
    width: 800
    height: 1000

    ColumnLayout {
        anchors.fill: parent


        TaperView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 40
        }
    }
}
