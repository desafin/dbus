// myreceiver.h
#include <QObject>
#include <QDebug>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>
//#include <QDBusSignal>

class MyReceiver : public QObject
{
    Q_OBJECT

signals:
    void messageReceived(const QString &message);

public:
    MyReceiver(QObject *parent = nullptr);

public slots:
    void onHelloWorldReceived(const QString &message);
};
