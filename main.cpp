#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDBusConnection>
#include "myreceiver.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    MyReceiver myReceiver;

    // D-Bus 세션 버스에 서비스 등록
        if (!QDBusConnection::sessionBus().registerService("com.example.myapp"))
        {
            qDebug() << "Unable to register service on D-Bus";
            return -1;
        }

        // D-Bus 객체 경로에 서비스 객체 등록
        if (!QDBusConnection::sessionBus().registerObject("/myservice", &myReceiver))
        {
            qDebug() << "Unable to register object on D-Bus";
            return -1;
        }

    return app.exec();
}
