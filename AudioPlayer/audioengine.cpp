#include "audioengine.h"

AudioEngine::AudioEngine(QObject *parent):QObject(parent){
    m_player = new QMediaPlayer(this);
    m_audioOut = new QAudioOutput(this);
    m_player->setAudioOutput(m_audioOut);

    connect(m_player, &QMediaPlayer::positionChanged,
            this,     &AudioEngine::onPositionChanged);
    connect(m_player, &QMediaPlayer::durationChanged,
            this,     &AudioEngine::onDurationChanged);

    connect(m_player, &QMediaPlayer::playbackStateChanged,
            this,     &AudioEngine::onPlaybackStateChanged);
}
    bool AudioEngine::isPlaying()const{
        return m_isPlaying;
    }
    qint64 AudioEngine::getPosition()const{
        return m_player->position();
    }
    qint64 AudioEngine::getDuration()const{
        return m_player->duration();
    }

    void AudioEngine::play()
    {
        m_player->setSource(QUrl::fromLocalFile("D:/Google Disk/Music/Linkin Park - Numb.mp3"));
        m_player->play();
    }

    void AudioEngine::pause()
    {
        m_player->pause();
    }

    void AudioEngine::stop()
    {
        m_player->stop();
    }

    void AudioEngine::seek(qint64 positionMs)
    {
        m_player->setPosition(positionMs);
    }

    void AudioEngine::load_track(const QUrl& url)
    {
        m_player->setSource(url);
        play();
    }
    void AudioEngine::onPlaybackStateChanged(QMediaPlayer::PlaybackState state){
        m_isPlaying = (state == QMediaPlayer::PlayingState);
        emit isPlayingChanged();
    }


    void AudioEngine::onPositionChanged(qint64 position)
    {
        emit positionChanged(position);
    }

    void AudioEngine::onDurationChanged(qint64 duration)
    {
        emit durationChanged(duration);
    }


