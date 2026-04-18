#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

class AudioEngine: public QObject{
    Q_OBJECT
public:
    explicit AudioEngine(QObject* parent = nullptr);
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged)
    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)




};

#endif
