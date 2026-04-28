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
    Q_PROPERTY(qint64 position READ getPosition NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ getDuration NOTIFY durationChanged)


    bool isPlaying()const;
    qint64 getPosition()const;
    qint64 getDuration()const;

public slots:
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void seek(qint64 positionMs);
    Q_INVOKABLE void load_track(const QUrl& url);

signals:
    void isPlayingChanged();
    void positionChanged(qint64 position);
    void durationChanged(qint64 position);

private slots:
    void onPositionChanged(qint64 position);
    void onDurationChanged(qint64 duration);
    void onPlaybackStateChanged(QMediaPlayer::PlaybackState state);
private:
    QMediaPlayer* m_player;
    QAudioOutput* m_audioOut;
    bool m_isPlaying = false;
};

#endif
