#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMediaMetaData>
#include <QImage>
#include <QBuffer>
#include <QByteArray>
#include <QList>



class AudioEngine: public QObject{
    Q_OBJECT
public:
    explicit AudioEngine(QObject* parent = nullptr);
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged)
    Q_PROPERTY(qint64 position READ getPosition NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ getDuration NOTIFY durationChanged)
    Q_PROPERTY(QString albumArtBase64 READ albumArtBase64 NOTIFY metaDataChanged)
    Q_PROPERTY(QString get_song READ get_song NOTIFY metaDataChanged)
    Q_PROPERTY(QString get_artist READ get_artist NOTIFY metaDataChanged)

    // Q_PROPERTY(qreal volume READ getVolume  NOTIFY onVolumeChanged)

    bool isPlaying()const;
    qint64 getPosition()const;
    qint64 getDuration()const;
    void load_list();
    void initDatabase();
    QString albumArtBase64();
    void getDataFromDatabase();

    struct Track{
        int path;
        QString name;
        QString artist;
        int duration;
    };



    //qreal getVolume()const;

public slots:
    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void seek(qint64 positionMs);
    Q_INVOKABLE void load_track();
    Q_INVOKABLE void track_forward();
    Q_INVOKABLE void track_back();
    Q_INVOKABLE void set_volume(qreal volume);
    Q_INVOKABLE QImage get_albomIco();
    Q_INVOKABLE QString get_song();
    Q_INVOKABLE QString get_artist();
    Q_INVOKABLE void delete_track();
    Q_INVOKABLE void changeRepeat();


signals:
    void isPlayingChanged();
    void positionChanged(qint64 position);
    void durationChanged(qint64 position);
    void metaDataChanged();

  //  void volumeChanged(qreal volume);

private slots:
    void onPositionChanged(qint64 position);
    void onDurationChanged(qint64 duration);
    void onPlaybackStateChanged(QMediaPlayer::PlaybackState state);
    void onMetaDataChanged();
    void onStatusChanged(QMediaPlayer::MediaStatus status);

  //  void onVolumeChanged(qreal volume);
private:
    QMediaPlayer* m_player;
    QAudioOutput* m_audioOut;
    bool m_isPlaying = false;
    QSqlDatabase m_db;
    QList<QUrl> playList;
    QList<QUrl>::iterator pointer = playList.begin();
    QImage albumImage;
    bool isRepeat = false;
    QList<Track> m_songList;

};

#endif
