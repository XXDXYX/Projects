#include "monitor.h"

SysMonitor::SysMonitor(QObject *parent):QObject(parent){
    connect(timer, &QTimer::timeout, this, &SysMonitor::setCPU);
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
        totalDelta = delta_kernel + delta_user;  // весь CPU time за интервал
        busyDelta  = totalDelta - delta_idle;   // сколько из этого — не простой
        if (totalDelta > 0) // защита от деления на 0 (первый тик, либо аномалия)
        {
            cpuUsage = (static_cast<double>(busyDelta) / static_cast<double>(totalDelta)) * 100.0;
        }
        prev_idleTime = idleTime;
        prev_kernelTime = kernelTime;
        prev_userTime = userTime;
        qDebug() << "CPU: " << cpuUsage;
        emit cpuUsageChanged();
}

double SysMonitor::getCPU(){
    return cpuUsage;
}