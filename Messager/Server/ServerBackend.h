#ifndef SERVERBACKEND_H
#define SERVERBACKEND_H
#include <QObject>
#include <QDebug>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <ws2tcpip.h>
#include <thread>
#include <mutex>
#include <string>

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
                    emit getString("Friend connected");
                    std::thread([this, clientSoc]() { Client(clientSoc); }).detach();
                }
                else{
                    emit errorCode(2);
                }
        }
    }
    Q_INVOKABLE void startServer() {
        std::thread([this]() {set_socket(); }).detach();
    }
    void Client(SOCKET clientSoc) {
        std::string str;
        int receivedBytes = 0;
        char buffer[1024];
        do {
            receivedBytes = recv(clientSoc, buffer, 1024, 0);
            if (receivedBytes <= 0) {
                break;
            } else if (receivedBytes > 0) {
                buffer[receivedBytes] = '\0';
                str.append(buffer, receivedBytes);
                if (str.find('\n') != std::string::npos || str.find('\r') != std::string::npos) {
                    emit newMessageReceived(QString::fromStdString(str));
                    str.clear();
                }
            }
        } while (receivedBytes > 0);
         closesocket(clientSoc);
    }
signals:
    void btn_sendMessage();
    void newMessageReceived(QString text);
    void errorCode(int code);
    void getString(std::string str);
public slots:
    void sendMessage(const QString &value){
        if (socket_buf == INVALID_SOCKET) return;
        QString str = value;
         str += "\n";
        const char* cstr = str.toUtf8().constData();
        std::lock_guard<std::mutex>lg(mtx);
        send(socket_buf, cstr, str.length(), 0);
    }
    //void getMessage(const QString &text);
};
#endif
