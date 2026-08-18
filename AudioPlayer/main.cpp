<<<<<<< HEAD
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
=======
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

>>>>>>> audio_player_branch
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
<<<<<<< HEAD
    engine.loadFromModule("AudioPlayer", "Main");
=======
        engine.loadFromModule("AudioPlayer", "Main");
>>>>>>> audio_player_branch

    return app.exec();
}
