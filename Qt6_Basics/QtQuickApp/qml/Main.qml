import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 300
    title: "Qt 6 Minimal App"

    Rectangle {
        anchors.fill: parent
        color: "#202020"

        Text {
            anchors.centerIn: parent
            text: "Hello from QML!"
            color: "white"
            font.pixelSize: 24
        }
    }
}

