#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "monitor.h"
#include "monitorGPU.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    SysMonitor monitor;
    GpuMonitor gpuMonitor;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("monitor",&monitor);
    engine.rootContext()->setContextProperty("gpu",&gpuMonitor);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("SystemMonitor", "Main");

    return QGuiApplication::exec();
}
