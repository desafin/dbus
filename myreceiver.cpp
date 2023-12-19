// myreceiver.cpp
#include "myreceiver.h"

MyReceiver::MyReceiver(QObject *parent) : QObject(parent)
{
    QDBusConnection::sessionBus().connect("com.example.MySignal", "/com/example/MySignal",
                                          "com.example.MySignal", "HelloWorld",
                                          this, SLOT(onHelloWorldReceived(QString)));
}

void MyReceiver::onHelloWorldReceived(const QString &message)
{
    qDebug() << "Received message:" << message;
    // 여기서 QML로 메시지 전달
    emit messageReceived(message);
}
