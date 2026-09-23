#ifndef MONITORGPU_H
#define MONITORGPU_H
#include <QObject>
#include <windows.h>
#include <QDebug>
#include <QTimer>
#include <nvapi.h>

class GpuMonitor: public QObject{
    Q_OBJECT
    Q_PROPERTY(QString gpuName READ getGpuName CONSTANT)
    Q_PROPERTY(double gpuUsagePer READ getGpuUsage NOTIFY OnGpuUsageChanged)
    Q_PROPERTY(double gpuTem READ getGpuTem NOTIFY OnGpuTemChanged)
    Q_PROPERTY(unsigned long totalMemoryMB READ getTotalVram CONSTANT)
    Q_PROPERTY(unsigned long usedMemoryMB READ getUsageVram NOTIFY OnVramChanged)
public:
    explicit GpuMonitor(QObject* parent = nullptr);

    ~GpuMonitor();

private:
    bool m_available;
    NvU32 gpuCount = 0;
    double gpuUsagePer = 0;
    double gpuTem = 0;
    unsigned long totalMemoryMB = 0;
    unsigned long usedMemoryMB = 0;
    NvPhysicalGpuHandle hGpu[NVAPI_MAX_PHYSICAL_GPUS] = { 0 };;
    NV_GPU_DYNAMIC_PSTATES_INFO_EX gpuUsage;
    QTimer* timer = new QTimer(this);

    void setGpuTem();
    void setGpuUsage();
    void setVram();
public slots:
    NvU32 getNumGpu();
    QString getGpuName() const;
    double getGpuUsage() const;
    double getGpuTem() const;
    unsigned long getTotalVram()const;
    unsigned long getUsageVram()const;

signals:
    void OnGpuUsageChanged();
    void OnGpuTemChanged();
    void OnVramChanged();



};




#endif // MONITORGPU_H
