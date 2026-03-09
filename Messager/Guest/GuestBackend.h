#ifndef GUESTBACKEND_H
#define GUESTBACKEND_H
#include <QObject>
#include <QDebug>
#include <WinSock2.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <ws2tcpip.h>
#include <string>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
class Guest: public QObject{
    Q_OBJECT
    public:
    explicit Guest(QObject *parent = nullptr) : QObject(parent) {
    }

mutex mt;

void Client(SOCKET clientSoc) {
    string message;
    int receivedBytes = 0;
    char buffer[1024];
    do {
        receivedBytes = recv(clientSoc, buffer, 1024, 0);
        if (receivedBytes > 0) {
            buffer[receivedBytes] = '\0';
            message.append(buffer, receivedBytes);
            if (message.find('\n') != string::npos || message.find('\r') != string::npos) {
                lock_guard<mutex> lg(mt);
                qDebug()  << "\r" << string(80, ' ') << "\r";
                qDebug()  << message;
                qDebug()  << "Me: ";
                cout.flush();
                message.clear();
            }
        } else if (receivedBytes == 0) {
            qDebug()  << "Client disconnected";
            break;
        } else {
            qDebug() << "recv failed";
            break;
        }

    } while (true);
    closesocket(clientSoc);
}
Q_INVOKABLE void connect_Guest() {
    std::thread([this]() { guest_client(); }).detach();
}
void Server(SOCKET clientSoc) {
    string myReply;
    while (true) {
        qDebug() << "Me: ";
        getline(cin, myReply);
        lock_guard<mutex>lg(mt);
        myReply += "\n";
        send(clientSoc, myReply.c_str(), myReply.length(), 0);

    }
}
 int guest_client()
{
    WSAData wsData;
    WSAStartup(MAKEWORD(2, 2), &wsData);
    auto soc = socket(AF_INET, SOCK_STREAM, 0);
    if (soc != INVALID_SOCKET) {
        qDebug()  << "Socket is correct!!\n";
    }
    else {
        qDebug() << "Socket isn`t correct!!\n";
    }

    addrinfo hints, * result = NULL;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    const char* pinggy_host = "phlir-195-225-49-21.a.free.pinggy.link";
    const char* pinggy_port = "36689";

    int res = getaddrinfo(pinggy_host, pinggy_port, &hints, &result);
    if (res != 0) {
        qDebug() << "DNS Error: " << res ;
        return -1;
    }
    if (::connect(soc, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        qDebug()  << "Connection failed! Error: " << WSAGetLastError();
        freeaddrinfo(result);
        return -1;
    }
    freeaddrinfo(result);
    qDebug()  << "Connected to friend via Pinggy!";

    std::thread cl([this, &soc](){Client(ref(soc));});
    std::thread server([this, &soc]() { Server(ref(soc));});
    cl.join();
    server.join();

    closesocket(soc);
    WSACleanup();
    return 0;
}

};
#endif
