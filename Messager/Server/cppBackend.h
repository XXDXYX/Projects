#ifndef CPPBACKEND_H
#define CPPBACKEND_H
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
    std::mutex mtx;
    Q_INVOKABLE void set_socket() {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2,2),&wsaData);
        auto soc = socket(AF_INET, SOCK_STREAM, 0);
        if (soc != INVALID_SOCKET) {
            qDebug() << "Socket was created";
        }
        else {
             qDebug() << "Socket wasn`t created";
        }
        sockaddr_in sockadr;
        sockadr.sin_family = AF_INET;
        sockadr.sin_port = htons(49153);
        sockadr.sin_addr.S_un.S_addr = INADDR_ANY;
        bind(soc, (sockaddr*)&sockadr, sizeof(sockadr));
        listen(soc, SOMAXCONN);
        qDebug() << "Waiting for connection...";
        while (true) {
            SOCKET clientSoc = accept(soc, nullptr, nullptr);
            qDebug() << "\nFriend connected!!!";
            std::thread client([this, &clientSoc]() { Client(std::ref(clientSoc)); });
            std::thread server([this, &clientSoc]() { Server(std::ref(clientSoc)); });

            client.join();
            server.join();


        }

    }
    Q_INVOKABLE void startServer() {
        std::thread([this]() { set_socket(); }).detach();
    }
    Q_INVOKABLE void Client(SOCKET clientSoc) {
        std::string str;
        int receivedBytes = 0;
        char buffer[1024];
        do {
            receivedBytes = recv(clientSoc, buffer, 1024, 0);
            if (receivedBytes <= 0) {
                qDebug() << "Connection lost...";
                break;
            } else if (receivedBytes > 0) {
                buffer[receivedBytes] = '\0';
                str.append(buffer, receivedBytes);
                if (str.find('\n') != std::string::npos || str.find('\r') != std::string::npos) {
                    std::lock_guard<std::mutex> lg(mtx);
                    qDebug() << "\r" << std::string(80, ' ') << "\r";
                    qDebug() << str;
                    qDebug() << "Server: ";
                    str.clear();
                }
            }
        } while (receivedBytes > 0);
    }
    Q_INVOKABLE void Server( SOCKET clientSoc) {
        while (true) {

            QTextStream cin(stdin);
            qDebug() << "Server: ";
            QString str = cin.readLine();
            const char* cstr = str.toUtf8().constData();
            std::lock_guard<std::mutex>lg(mtx);
            str += "\n";
            send(clientSoc, cstr, str.length(), 0);
        }
    }
};
#endif
