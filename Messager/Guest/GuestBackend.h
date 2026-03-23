#ifndef GUESTBACKEND_H
#define GUESTBACKEND_H
#include <QObject>
#include <QDebug>
#include <WinSock2.h>
#include <thread>
#include <mutex>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
class Guest: public QObject{
    Q_OBJECT
    public:
    explicit Guest(QObject *parent = nullptr) : QObject(parent) {
    }
std::mutex mt;
SOCKET socket_buf = INVALID_SOCKET;
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

    const char* pinggy_host = "puogu-195-225-49-21.a.free.pinggy.link";
    const char* pinggy_port = "45193";
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
    std::thread cl([this, soc](){ Client(); });
    cl.detach();
    return 0;
}
void Client() {
    QString message;
    int receivedBytes = 0;
    char buffer[1024];
    do {
        receivedBytes = recv(socket_buf, buffer, 1024-1, 0);
        if (receivedBytes <= 0) {
            break;
        } else if (receivedBytes > 0) {
            buffer[receivedBytes] = '\0';
            message.append(QString::fromUtf8(buffer, receivedBytes));
            if (message.contains('\n') || message.contains('\r')) {
                QString msg = message.trimmed();
                message.clear();
                QMetaObject::invokeMethod(this, [this, msg]() {
                    emit newMessageReceived(msg);
                }, Qt::QueuedConnection);
            }
        }

    } while (receivedBytes > 0);
    closesocket(socket_buf);
}
Q_INVOKABLE void connect_Guest() {
    std::thread([this]() { guest_client(); }).detach();
}
signals:

    void newMessageReceived(QString text);
    void errorOccurred(int code);
public slots:
    void sendMessage(const QString &value){
        if (socket_buf == INVALID_SOCKET) return;
        QString str = value;
        str += "\n";
        QByteArray bytes = str.toUtf8();
        std::lock_guard<std::mutex>lg(mt);
        send(socket_buf, bytes.constData(), bytes.size(), 0);
}


};
#endif
