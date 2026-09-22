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
    Q_PROPERTY(DWORD usageRAM READ getUsageRAM NOTIFY ramUsageChanged)
    Q_PROPERTY(DWORD totalRAM READ getTotalRAM NOTIFY ramUsageChanged)
    Q_PROPERTY(double totalMb READ getTotalMb NOTIFY ramUsageChanged)
    Q_PROPERTY(double usageMb READ getUsageMb NOTIFY ramUsageChanged)
    Q_PROPERTY(QString processorName READ getProcessorName CONSTANT)
public:
    explicit SysMonitor(QObject* parent = nullptr);
    static ULONGLONG FileTimeToUInt64(const FILETIME& ft);

public slots:
    double getCPU() const;
    DWORD getUsageRAM() const;
    DWORD getTotalRAM() const;
    double getUsageMb() const;
    double getTotalMb() const;
    QString getProcessorName();

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
    MEMORYSTATUSEX lpBuffer;
    DWORD usageRam = 0.0, totalRam = 0.0;
    double totalMb;
    double usageMb;
    QString processorName;

signals:
    void cpuUsageChanged();
    void ramUsageChanged();

private slots:
    void setCPU();
    void setRAM();
    void setData(FILETIME& Idle,FILETIME& Kernel,FILETIME& User);

};


#endif // MONITOR_H
