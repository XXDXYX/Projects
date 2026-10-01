#ifndef MONITORNET_H
#define MONITORNET_H


#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2ipdef.h>
#include <windows.h>
#include <iphlpapi.h>
#include <netioapi.h>

#include <QObject>
#include <QDebug>
#include <QTimer>

class NetworkMonitor: public QObject{
    Q_OBJECT
    Q_PROPERTY(double download READ getDownload NOTIFY onNetworkChanges)
    Q_PROPERTY(double upload READ getUpload NOTIFY onNetworkChanges)

public:
    explicit NetworkMonitor(QObject* parent = nullptr);

    ~NetworkMonitor();
private:
    QTimer* timer = new QTimer(this);
    MIB_IF_TABLE2* table = nullptr;
    DWORD status = 0;
    NET_LUID interFace;
    bool hasFirstSample = false;
    ULONG64 prevInOctets = 0;
    ULONG64 prevOutOctets = 0;
    ULONG64 inOctets = 0;
    ULONG64 outOctets = 0;
    double download = 0;
    double upload = 0;

    void initNetwork();
    void setNetworkSpeed();



public slots:
    double getDownload()const;
    double getUpload()const;


signals:
    void onNetworkChanges();


};





#endif // MONITORNET_H
