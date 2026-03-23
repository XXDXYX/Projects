#ifndef SERVERBACKEND_H
#define SERVERBACKEND_H
#include <QObject>
#include <QDebug>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <ws2tcpip.h>
#include <thread>
#include <mutex>


class Connect :public QObject{
    Q_OBJECT
public:
    explicit Connect(QObject *parent = nullptr) : QObject(parent) {
    }
    SOCKET socket_buf = INVALID_SOCKET;
    std::mutex mtx;

    int set_socket() {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2,2),&wsaData);
        auto soc = socket(AF_INET, SOCK_STREAM, 0);
        if (soc == INVALID_SOCKET) {
            emit errorCode(1);
            return 1;
        }
        sockaddr_in sockadr;
        sockadr.sin_family = AF_INET;
        sockadr.sin_port = htons(49152);
        sockadr.sin_addr.S_un.S_addr = INADDR_ANY;
        bind(soc, (sockaddr*)&sockadr, sizeof(sockadr));
        listen(soc, SOMAXCONN);
     qDebug() << "Waiting for connection...";
        while (true) {
            SOCKET clientSoc = accept(soc, nullptr, nullptr);
                if(clientSoc != INVALID_SOCKET){
                    std::lock_guard<std::mutex> lg(mtx);
                    this->socket_buf = clientSoc;
                    qDebug() << "Connect succesful";
                    std::thread([this]() { received_msg(); }).detach();
                }
                else{
                    emit errorCode(2);
                }
        }
    }
    Q_INVOKABLE void startServer() {
        std::thread([this]() {set_socket(); }).detach();
    }
    void received_msg(){
        QString text;
        int receivedBytes = 0;
        char buffer[1024];
        do {
            receivedBytes = recv(socket_buf, buffer, 1023, 0);
            if (receivedBytes <= 0) {
                break;
            } else if (receivedBytes > 0) {
                buffer[receivedBytes] = '\0';
                text.append(QString::fromUtf8(buffer, receivedBytes));
                if (text.contains('\n') || text.contains('\r')) {
                    QString msg = text.trimmed();
                    text.clear();
                    QMetaObject::invokeMethod(this, [this, msg]() {
                        emit newMessageReceived(msg);
                    }, Qt::QueuedConnection);
                }
            }
        } while (receivedBytes > 0);
    }

signals:
    void btn_sendMessage();
    void newMessageReceived(QString text);
    void errorCode(int code);
public slots:
    void sendMessage(const QString &value){
        if (socket_buf == INVALID_SOCKET) return;
        QString str = value;
         str += "\n";
        QByteArray bytes = str.toUtf8();
        std::lock_guard<std::mutex>lg(mtx);
        send(socket_buf, bytes.constData(), bytes.size(), 0);
    }

};
#endif
