#include "monitorGPU.h"

GpuMonitor::GpuMonitor(QObject* parent) : QObject(parent){
    NvAPI_Status status = NvAPI_Initialize();
    if (status != NVAPI_OK) {
        qDebug() << "NVAPI failed to initialize, status:" << status;
        m_available = false;
        return;
    }
    m_available = true;
    getNumGpu();
    setVram();
    connect(timer, &QTimer::timeout, this, &GpuMonitor::setGpuUsage);
    connect(timer, &QTimer::timeout, this, &GpuMonitor::setGpuTem);
    connect(timer, &QTimer::timeout, this, &GpuMonitor::setVram);

    timer->start(1000);
}

NvU32 GpuMonitor::getNumGpu(){
    NvAPI_Status status;
    status = NvAPI_EnumPhysicalGPUs(hGpu, &gpuCount);
    if(status != NVAPI_OK || gpuCount == 0){
        return 0;
    }else{
        return gpuCount;
    }
}

double GpuMonitor::getGpuUsage() const{
    return gpuUsagePer;
}


QString GpuMonitor::getGpuName() const{
    NvAPI_ShortString gpuName;
    NvAPI_Status status = NvAPI_GPU_GetFullName(hGpu[0], gpuName);
    if (status != NVAPI_OK) {
        return " ";
    }
    QString qstr = QString::fromUtf8(gpuName);
    return qstr;
}

double GpuMonitor::getGpuTem()const{
    return gpuTem;
}

unsigned long GpuMonitor::getTotalVram()const{
    return totalMemoryMB;
}

unsigned long GpuMonitor::getUsageVram() const{
    return usedMemoryMB;
}

void GpuMonitor::setGpuUsage(){
    gpuUsage.version = NV_GPU_DYNAMIC_PSTATES_INFO_EX_VER;
    NvAPI_Status status = NvAPI_GPU_GetDynamicPstatesInfoEx(hGpu[0], &gpuUsage);
    gpuUsagePer = gpuUsage.utilization[0].percentage;
    if (status != NVAPI_OK) {
        qDebug() << GetLastError();
        return;
    }
    emit OnGpuUsageChanged();
}

void GpuMonitor::setGpuTem(){
    NV_GPU_THERMAL_SETTINGS pThermalSettings = {0};
    pThermalSettings.version = NV_GPU_THERMAL_SETTINGS_VER;
    NvAPI_Status status = NvAPI_GPU_GetThermalSettings(hGpu[0],NVAPI_THERMAL_TARGET_ALL, &pThermalSettings);
    if (status != NVAPI_OK) {
        qDebug() << GetLastError();
        return;
    }
    gpuTem = pThermalSettings.sensor[0].currentTemp;
    emit OnGpuTemChanged();
}

void GpuMonitor::setVram(){
    NV_GPU_MEMORY_INFO_EX pMemoryInfo = {0};
    pMemoryInfo.version = NV_GPU_MEMORY_INFO_EX_VER;
    NvAPI_Status status = NvAPI_GPU_GetMemoryInfoEx(hGpu[0], &pMemoryInfo);
    if (status != NVAPI_OK) {
        qDebug() << GetLastError();
        return;
    }
    totalMemoryMB = pMemoryInfo.dedicatedVideoMemory / 1024 / 1024;
    unsigned long freeMemoryMB = pMemoryInfo.curAvailableDedicatedVideoMemory / 1024 / 1024;
    usedMemoryMB = totalMemoryMB - freeMemoryMB;
    qDebug() << "dedicatedVideoMemory (raw):" << pMemoryInfo.dedicatedVideoMemory;
    qDebug() << "curAvailableDedicatedVideoMemory (raw):" << pMemoryInfo.curAvailableDedicatedVideoMemory;
    emit OnVramChanged();
}

GpuMonitor::~GpuMonitor(){
    if(m_available){
        NvAPI_Unload();
    }
}