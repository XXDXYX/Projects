#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "monitorCPU.h"
#include "monitorGPU.h"
#include "monitorNet.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    SysMonitor monitor;
    GpuMonitor gpuMonitor;
    NetworkMonitor network;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("monitor",&monitor);
    engine.rootContext()->setContextProperty("gpu",&gpuMonitor);
    engine.rootContext()->setContextProperty("network",&network);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SystemMonitor", "Main");

    return QGuiApplication::exec();
}
