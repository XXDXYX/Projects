#ifndef GUESTBACKEND_H
#define GUESTBACKEND_H
#include <QObject>
#include <QDebug>
#include <WinSock2.h>
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
SOCKET socket_buf;
int error_code;
int guest_client()
{
    WSAData wsData;
    WSAStartup(MAKEWORD(2, 2), &wsData);
    auto soc = socket(AF_INET, SOCK_STREAM, 0);
    if (soc == INVALID_SOCKET) {
        emit errorOccurred(1);
        return 1;
    }
    addrinfo hints, * result = NULL;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    const char* pinggy_host = "vxbob-195-225-49-21.a.free.pinggy.link";
    const char* pinggy_port = "41483";
    socket_buf = soc;
    int res = getaddrinfo(pinggy_host, pinggy_port, &hints, &result);
    if (res != 0) {
        emit errorOccurred(2);
        return 2;
    }
    if (::connect(soc, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        freeaddrinfo(result);
        emit errorOccurred(3);
        return 3;
    }
    freeaddrinfo(result);
    qDebug()  << "Connected to friend via Pinggy!";
    std::thread cl([this, soc](){ Client(soc); });
    cl.detach();
    return 0;
}
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
                emit newMessageReceived(QString::fromStdString(message));
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
signals:
    void btn_sendMessage();
    void newMessageReceived(QString text);
    void errorOccurred(int code);
public slots:
    void sendMessage(const QString &value){
        if (socket_buf == INVALID_SOCKET) return;
        QString str = value;
        str += "\n";
        const char* cstr = str.toUtf8().constData();
        std::lock_guard<std::mutex>lg(mt);
        send(socket_buf, cstr, str.length(), 0);
}
   // void getMessage(const QString &text);

};
#endif
