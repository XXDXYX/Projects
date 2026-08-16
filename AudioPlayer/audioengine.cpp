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
    QImage albumImage;
   // QFile file("C:/Users/Lenovo/Desktop/Projects/AudioPlayer/list.txt");



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
    QString AudioEngine::get_song(){
        QMediaMetaData meta = m_player->metaData();
        QString title;
        if (!meta.value(QMediaMetaData::Title).isNull()) {
            title = meta.value(QMediaMetaData::Title).toString();
        }else{
            title = "Unknown song";
        }
        return title;
    }

    void AudioEngine::load_list(){
        QSqlQuery query;
        query.exec("SELECT path FROM tracks");
        while(query.next()){
            QString path = query.value("path").toString();
            playList.append(QUrl::fromLocalFile(path));
        }
        if(!playList.isEmpty()){
            pointer = playList.begin();
            m_player->setSource((*pointer));
        }
    }

    void AudioEngine::track_forward(){
        if(!playList.isEmpty() && pointer != playList.end()){
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
    QString AudioEngine::get_artist(){
        QMediaMetaData meta = m_player->metaData();
        QString artist;
        if (!meta.value(QMediaMetaData::ContributingArtist).isNull()) {
            artist = meta.value(QMediaMetaData::ContributingArtist).toString();
        }else{
            artist = "Unknowm artist";
        }
        return artist;
    }
    void AudioEngine::onDurationChanged(qint64 duration)
    {
        emit durationChanged(duration);
    }
    QImage AudioEngine::get_albomIco(){

        QMediaMetaData meta = m_player->metaData();
         qDebug() << "meta keys:" << meta.keys();
        if(!meta.value(QMediaMetaData::ThumbnailImage).isNull()) {
            QVariant coverVar = meta.value(QMediaMetaData::ThumbnailImage);
            albumImage = coverVar.value<QImage>();
             qDebug() << "cover size:" << albumImage.size();
            return albumImage;
        }else{
            return QImage("albumFoto.png");;
        }

    }
    QString AudioEngine::albumArtBase64(){

        QImage img=get_albomIco();
         qDebug() << "albumArtBase64 called, img null:" << img.isNull();
        if (img.isNull()) {
            return "";
        }

        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        img.save(&buffer, "PNG");
        qDebug() << "byteArray size:" << byteArray.size();
        return "data:image/png;base64," + QString::fromLatin1(byteArray.toBase64());
    }
    void AudioEngine::onMetaDataChanged(){

        QMediaMetaData meta = m_player->metaData();
         if (!meta.isEmpty()) {
        QString path = m_player->source().toLocalFile();
        qDebug() << "onMetaDataChanged called, path:" << path;
        qDebug() << "meta empty:" << meta.isEmpty();
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
        emit metaDataChanged();
        qDebug() << "metaDataChanged emitted";
    }

