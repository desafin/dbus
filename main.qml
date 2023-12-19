// main.qml
import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.15
ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "D-Bus Example"

    Text {
        id: messageText
        text: "Waiting for message..."
        color: "white"
    }

    Connections {
        target: myReceiver
        onMessageReceived: {
            messageText.text = message
        }
    }
}
