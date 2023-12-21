#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QCoreApplication>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>


#define SERVICE_NAME "com.example.mydbus.service"
#define OBJECT_PATH "/com/example/mydbus/object"
#define INTERFACE_NAME "com.example.mydbus.interface"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // D-Bus 서비스 등록
    if (!QDBusConnection::systemBus().registerService(SERVICE_NAME)) {
        qDebug() << "D-Bus 서비스 등록 실패";
        return -1;
    }

    // D-Bus 오브젝트 등록
    QObject myObject;
    QDBusConnection::systemBus().registerObject(OBJECT_PATH, &myObject);

    // D-Bus 시그널 보내기
    QDBusMessage signal = QDBusMessage::createSignal(OBJECT_PATH, INTERFACE_NAME, "mySignal");
    signal << QString("Hello, D-Bus!");
    QDBusConnection::systemBus().send(signal);

    return app.exec();
}

