#ifndef MONITOR_H
#pragma once
#define MONITOR_H
#include <QObject>
#include <windows.h>
#include <QDebug>
#include <QTimer>
class SysMonitor: public QObject{
    Q_OBJECT
    Q_PROPERTY(double cpuUsage READ getCPU NOTIFY cpuUsageChanged)

public:
    explicit SysMonitor(QObject* parent = nullptr);
    static ULONGLONG FileTimeToUInt64(const FILETIME& ft);
    void setData(FILETIME& Idle,FILETIME& Kernel,FILETIME& User);
    double getCPU();
public slots:



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
    QTimer *timer = new QTimer(this);
    double cpuUsage = 0.0;
signals:
    void cpuUsageChanged();


private slots:
    void setCPU();

};


#endif // MONITOR_H
