#include "monitor.h"

SysMonitor::SysMonitor(QObject *parent):QObject(parent){


}

static ULONGLONG FileTimeToUInt64(const FILETIME& ft){
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



double SysMonitor::getCPU(){
    if(!GetSystemTimes(&idle,&kernel,&user)){
        qDebug() << "Error with GetSystemTimes" << GetLastError();
        return -1;
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
        double cpuUsagePercent = 0.0;
        if (totalDelta > 0) // защита от деления на 0 (первый тик, либо аномалия)
        {
            cpuUsagePercent = (static_cast<double>(busyDelta) / static_cast<double>(totalDelta)) * 100.0;
        }
        prev_idleTime = idleTime;
        prev_kernelTime = kernelTime;
        prev_userTime = userTime;
        return cpuUsagePercent;
}


FILETIME SysMonitor::getData(){

}