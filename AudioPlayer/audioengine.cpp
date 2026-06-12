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

    connect(m_player, &QMediaPlayer::metaDataChanged,
            this,&AudioEngine::onMetaDataChanged);


    initDatabase();
    load_list();
}

    QFile file("C:/Users/Lenovo/Desktop/Projects/AudioPlayer/list.txt");



void AudioEngine::initDatabase(){
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("my_database.db");
        if (!m_db.open()) {
            qDebug() << "Database is not open:" << m_db.lastError().text();
            return;
        }
        qDebug() << "Database is opened correctly";
        QSqlQuery tracks;
        tracks.exec( "CREATE TABLE IF NOT EXISTS tracks ("
                    "id       INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "path     TEXT UNIQUE, "
                    "title    TEXT, "
                    "artist   TEXT, "
                    "album    TEXT, "
                    "duration INTEGER"
                    ")"
                    );
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

    void AudioEngine::set_volume(qreal volume){
        m_audioOut->setVolume(volume);
    }

    void AudioEngine::load_list(){
        QSqlQuery query;
        query.exec("SELECT path FROM tracks");
        while(query.next()){
            QString path = query.value("path").toString();
            playList.append(path);
        }
        if(!playList.isEmpty()){
            pointer = playList.begin();
            m_player->setSource((*pointer));
        }
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
    void AudioEngine::onMetaDataChanged(){
        QString path = m_player->source().toLocalFile();
        if (path.isEmpty()){
            return;
        }

        QMediaMetaData meta = m_player->metaData();
        QString title;
        QString artist;
        qint64 duration;
        QString album;
        if(meta.isEmpty()){
            return;
        }
        if (!meta.value(QMediaMetaData::Title).isNull()) {
            title = meta.value(QMediaMetaData::Title).toString();
        }
        if (!meta.value(QMediaMetaData::ContributingArtist).isNull()) {
            artist = meta.value(QMediaMetaData::ContributingArtist).toString();
        }
        if (!meta.value(QMediaMetaData::Duration).isNull()) {
           duration = meta.value(QMediaMetaData::Duration).toLongLong();
        }
        if (!meta.value(QMediaMetaData::AlbumTitle).isNull()) {
            album = meta.value(QMediaMetaData::AlbumTitle).toString();
        }

        QSqlQuery query;
        query.prepare(
            "INSERT OR IGNORE INTO tracks (path, title, artist, album, duration) "
            "VALUES (:path, :title, :artist, :album, :duration)"
            );
        query.bindValue(":path",     path);
        query.bindValue(":title",    title);
        query.bindValue(":artist",   artist);
        query.bindValue(":album",    album);
        query.bindValue(":duration", duration);

        if (!query.exec()) {
            qDebug() << "Insert error:" << m_db.lastError().text();
        }

    }

