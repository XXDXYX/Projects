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



QString GpuMonitor::getGpuName() const{
    NvAPI_ShortString gpuName;
    NvAPI_GPU_GetFullName(hGpu[0], gpuName);
    QString qstr = QString::fromUtf8(gpuName);
    return qstr;
}







GpuMonitor::~GpuMonitor(){
    if(m_available){
        NvAPI_Unload();
    }
}