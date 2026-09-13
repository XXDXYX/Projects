#include "monitor.h"

SysMonitor::SysMonitor(QObject *parent):QObject(parent){


}

static ULONGLONG FileTimeToUInt64(const FILETIME& ft){
    ULARGE_INTEGER uli;
    uli.LowPart  = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    return uli.QuadPart;
}

void SysMonitor::setData(FILETIME idleTime,FILETIME kernelTime,FILETIME userTime) const{
    GetSystemTimes(&idleTime,&kernelTime,&userTime);
    FileTimeToUInt64(idleTime);
    FileTimeToUInt64(kernelTime);
    FileTimeToUInt64(userTime);
}


FILETIME SysMonitor::getData(){

}