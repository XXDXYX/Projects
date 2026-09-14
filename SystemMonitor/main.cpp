#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "monitor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    SysMonitor monitor;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("monitor",&monitor);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SystemMonitor", "Main");

    return QGuiApplication::exec();
}
