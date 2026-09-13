#ifndef MONITOR_H
#pragma once
#define MONITOR_H
#include <QObject>
#include <windows.h>
class SysMonitor: public QObject{
    Q_OBJECT
    explicit SysMonitor(QObject* parent = nullptr);

    static ULONGLONG FileTimeToUInt64(const FILETIME& ft);
    void setData(FILETIME IdleTime,FILETIME KernelTime,FILETIME UserTime) const;

public slots:
    Q_INVOKABLE FILETIME getData();


public:


private:
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;
signals:


};


#endif // MONITOR_H
