
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "audioengine.h"
#include <QQmlContext>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    AudioEngine audEng;
    engine.rootContext()->setContextProperty("audEng",&audEng);


    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

        engine.loadFromModule("AudioPlayer", "Main");

        engine.loadFromModule("AudioPlayer", "Main");


    return app.exec();
}
