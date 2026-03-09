#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QDebug>
#include <winsock2.h>
#include <QQmlContext>
#pragma comment(lib,"ws2_32.lib")
#include <ws2tcpip.h>
#include "GuestBackend.h"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    Guest* guest = new Guest();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Guest",guest);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("GuestClient", "Main");
    return app.exec();
}
