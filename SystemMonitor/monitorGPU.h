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
public:
    explicit GpuMonitor(QObject* parent = nullptr);

    ~GpuMonitor();

private:
    bool m_available;
    NvU32 gpuCount = 0;
    NvPhysicalGpuHandle hGpu[NVAPI_MAX_PHYSICAL_GPUS] = { 0 };;
public slots:
    NvU32 getNumGpu();
    QString getGpuName() const;


signals:





};




#endif // MONITORGPU_H
