#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QDebug>
#include <winsock2.h>
#include <QQmlContext>
#pragma comment(lib,"ws2_32.lib")
#include <ws2tcpip.h>
#include "cppBackend.h"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    Connect con;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Connect",&con);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Ldjj", "Main");
    return app.exec();
}
