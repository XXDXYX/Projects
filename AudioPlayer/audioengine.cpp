#include "audioengine.h"
#include "QFileDialog"

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

    load_list();
}

    QFile file("C:/Users/Lenovo/Desktop/Projects/AudioPlayer/list.txt");

    bool AudioEngine::isPlaying()const{
        return m_isPlaying;
    }
    qint64 AudioEngine::getPosition()const{
        return m_player->position();
    }
    qint64 AudioEngine::getDuration()const{
        return m_player->duration();
    }
    QList<QUrl> playList;
    QList<QUrl>::iterator pointer = playList.begin();

    void AudioEngine::play()
    {
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


    void AudioEngine::load_list(){
        if(!file.open(QIODevice::ReadOnly)){
            qDebug() << "error";
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QUrl url = QUrl::fromLocalFile(line);
            playList.append(url);
        }
        file.close();

        if(!playList.isEmpty()){
            pointer = playList.begin();
            m_player->setSource((*pointer));
        }
    }
    void AudioEngine::append_list(QUrl url){
        if(!file.open(QIODevice::Append)){
            qDebug() << "error";
        }
            QTextStream out(&file);
            QString str = url.toLocalFile();
            out << str << "\n";
            file.close();

    }


    void AudioEngine::track_forward(){
        if(!playList.isEmpty() && pointer != --playList.end()){
            ++pointer;
            m_player->setSource((*pointer));
            play();
        }
    }
    void AudioEngine::track_back(){
        if(!playList.isEmpty() && pointer != playList.begin()){
            --pointer;
            m_player->setSource((*pointer));
            play();
        }
    }
    void AudioEngine::load_track()
    {
        QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open file"), "/home/", tr("(*.mp3 *.flac)"));
        QUrl url = QUrl::fromUserInput(fileName);
        if (playList.contains(url)) {
            return;
        }
        append_list(url);
        playList.append(url);
        pointer = --playList.end();
       m_player->setSource(*pointer);

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


