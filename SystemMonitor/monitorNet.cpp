#include <monitorNet.h>

NetworkMonitor::NetworkMonitor(QObject* parent): QObject(parent){

    connect(timer, &QTimer::timeout,this, &NetworkMonitor::setNetworkSpeed);


    initNetwork();
    timer->start(1000);
}

void NetworkMonitor::initNetwork(){
    status = GetIfTable2(&table);
    DWORD bestindex = 0;
    IN_ADDR addr;
    inet_pton(AF_INET, "8.8.8.8", &addr);
    if (GetBestInterface(addr.S_un.S_addr, &bestindex) != NO_ERROR) {
        qDebug() << "GetBestInterface failed";
        return;
    }
    if(status == NO_ERROR){

        for(unsigned long i = 0; i < table->NumEntries; ++i){
            const MIB_IF_ROW2 &row = table->Table[i];
            if(table->Table[i].OperStatus != IfOperStatusUp){
                continue;
            }
            if(table->Table[i].Type == IF_TYPE_SOFTWARE_LOOPBACK || table->Table[i].Type == IF_TYPE_TUNNEL){
                continue;
            }
            if(row.InterfaceIndex == bestindex){
             interFace = row.InterfaceLuid;
                break;
            }
        }

        FreeMibTable(table);
        table = nullptr;
    }else{
        qDebug() << "Error: " << status;
    }

}

void NetworkMonitor::setNetworkSpeed(){
    MIB_IF_ROW2 row = {0};
    row.InterfaceLuid = interFace;

    DWORD status = GetIfEntry2(&row);
    if (status != NO_ERROR) {
        qDebug() << "GetIfEntry2 failed:" << status;
        return;
    }
    if (!hasFirstSample) {
        prevInOctets = row.InOctets;
        prevOutOctets = row.OutOctets;
        hasFirstSample = true;
        return;
    }
    inOctets = row.InOctets - prevInOctets;
    outOctets = row.OutOctets - prevOutOctets;
    download = static_cast<double>(inOctets) / 1024.0/1024.0;
    upload = static_cast<double>(outOctets) / 1024.0/1024.0;
    prevInOctets = row.InOctets;
    prevOutOctets = row.OutOctets;
    emit onNetworkChanges();
}


double NetworkMonitor::getDownload() const{
    return download;
}

double NetworkMonitor::getUpload() const{
    return upload;
}

NetworkMonitor::~NetworkMonitor(){
    if (table != nullptr) {
        FreeMibTable(table);
    }
}