#include "monitor.h"

SysMonitor::SysMonitor(QObject *parent):QObject(parent){
    connect(timer, &QTimer::timeout, this, &SysMonitor::setCPU);
    connect(timer, &QTimer::timeout, this, &SysMonitor::setRAM);


    timer->start(1000);
}

ULONGLONG SysMonitor::FileTimeToUInt64(const FILETIME& ft){
    ULARGE_INTEGER uli;
    uli.LowPart  = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    return uli.QuadPart;
}

void SysMonitor::setData(FILETIME& idle,FILETIME &kernel,FILETIME& user){
    idleTime = FileTimeToUInt64(idle);
    kernelTime = FileTimeToUInt64(kernel);
    userTime = FileTimeToUInt64(user);
}

QString SysMonitor::getProcessorName(){
    HKEY hKey;
    LONG result = RegOpenKeyExW(
        HKEY_LOCAL_MACHINE,
        L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
        0,
        KEY_READ,
        &hKey
        );
    DWORD dataSize = 0;
    RegQueryValueExW(hKey, L"ProcessorNameString", nullptr, nullptr, nullptr, &dataSize);
    std::wstring buffer(dataSize / sizeof(wchar_t), L'\0'); // выделяем буфер под строку
    RegQueryValueExW(hKey, L"ProcessorNameString", nullptr, nullptr,
                     reinterpret_cast<LPBYTE>(buffer.data()), &dataSize);
    RegCloseKey(hKey);
    QString processorName = QString::fromWCharArray(buffer.c_str());
    return processorName;
}

void SysMonitor::setCPU(){
    if(!GetSystemTimes(&idle,&kernel,&user)){
        qDebug() << "Error with GetSystemTimes" << GetLastError();
        return ;
    }

    setData(idle,kernel,user);
    ULONGLONG delta_idle;
    ULONGLONG delta_user;
    ULONGLONG delta_kernel;
    ULONGLONG totalDelta;
    ULONGLONG busyDelta;
    if(hasFirstScreen == false){
        prev_idleTime = idleTime;
        prev_kernelTime = kernelTime;
        prev_userTime = userTime;
        hasFirstScreen = true;
    }
        delta_idle = idleTime - prev_idleTime;
        delta_kernel = kernelTime - prev_kernelTime;
        delta_user = userTime - prev_userTime;
        totalDelta = delta_kernel + delta_user;
        busyDelta  = totalDelta - delta_idle;
        if (totalDelta > 0)
        {
            cpuUsage = (static_cast<double>(busyDelta) / static_cast<double>(totalDelta)) * 100.0;
        }
        prev_idleTime = idleTime;
        prev_kernelTime = kernelTime;
        prev_userTime = userTime;
        qDebug() << "CPU: " << cpuUsage;
        emit cpuUsageChanged();
}

double SysMonitor::getCPU() const{
    return cpuUsage;
}

void SysMonitor::setRAM(){
    lpBuffer.dwLength = sizeof(MEMORYSTATUSEX);
    if(GlobalMemoryStatusEx(&lpBuffer)){
    usageRam = lpBuffer.dwMemoryLoad;
    totalMb = static_cast<double>(lpBuffer.ullTotalPhys) / (1024.0 * 1024.0);
    usageMb = static_cast<double>(lpBuffer.ullAvailPhys) / (1024.0 * 1024.0);
    qDebug() << lpBuffer.dwMemoryLoad;
    }else{
        qDebug() << "Error with RAM: " << GetLastError();
    }
    emit ramUsageChanged();
}

DWORD SysMonitor::getUsageRAM() const{
    return usageRam;
}
DWORD SysMonitor::getTotalRAM() const{
    return totalRam;
}
double SysMonitor::getTotalMb() const{
    return totalMb;
}
double SysMonitor::getUsageMb() const{
    return usageMb;
}