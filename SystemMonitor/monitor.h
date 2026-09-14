#ifndef MONITOR_H
#pragma once
#define MONITOR_H
#include <QObject>
#include <windows.h>
#include <QDebug>
class SysMonitor: public QObject{
    Q_OBJECT
public:
    explicit SysMonitor(QObject* parent = nullptr);
    static ULONGLONG FileTimeToUInt64(const FILETIME& ft);
    void setData(FILETIME& Idle,FILETIME& Kernel,FILETIME& User);

public slots:
    Q_INVOKABLE FILETIME getData();
    Q_INVOKABLE double getCPU();





private:
    FILETIME idle;
    FILETIME kernel;
    FILETIME user;
    ULONGLONG idleTime;
    ULONGLONG kernelTime;
    ULONGLONG userTime;
    ULONGLONG prev_idleTime = 0;
    ULONGLONG prev_kernelTime = 0;
    ULONGLONG prev_userTime = 0;
    bool hasFirstScreen = false;
signals:


};


#endif // MONITOR_H
