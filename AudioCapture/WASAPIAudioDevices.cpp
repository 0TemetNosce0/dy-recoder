#include "WASAPIAudioDevices.h"
#include <Windows.h>
#include <mmsystem.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <functiondiscoverykeys_devpkey.h>//PKEY_Device_FriendlyName
#include <QDebug>
//以下代码来自MSDN
#define EXIT_ON_ERROR(hres)  \
    if (FAILED(hres)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
    if ((punk) != NULL)  \
{ (punk)->Release(); (punk) = NULL; }

//const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
//const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
WASAPIAudioDevices::WASAPIAudioDevices()
{

}

WASAPIAudioDevices::~WASAPIAudioDevices()
{

}
/**
 * @brief WASAPIAudioDevices::GetWASAPIAudioDevices
 * @param devices
 * @param input true-音频输入 false-音频输出
 * @return 成功-true 错误-false
 */
bool WASAPIAudioDevices::GetWASAPIAudioDevices(QVector<AudioDeviceInfo> &devices, bool input)
{
    HRESULT hr = S_OK;
    IMMDeviceEnumerator *pEnumerator = NULL;
    IMMDeviceCollection *pCollection = NULL;
    IMMDevice *pEndpoint = NULL;
    IPropertyStore *pProps = NULL;
    LPWSTR pwszID = NULL;

    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator)/*CLSID_MMDeviceEnumerator*/, NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator)/*IID_IMMDeviceEnumerator*/,(void**)&pEnumerator);
    EXIT_ON_ERROR(hr)

            hr = pEnumerator->EnumAudioEndpoints(input?eCapture:eRender, DEVICE_STATE_ACTIVE, &pCollection);
    EXIT_ON_ERROR(hr)

            UINT  count;
    hr = pCollection->GetCount(&count);
    EXIT_ON_ERROR(hr)

            if (count == 0)
    {
        printf("No endpoints found.\n");
    }

    // Each loop prints the name of an endpoint device.
    for (ULONG i = 0; i < count; i++)
    {
        // Get pointer to endpoint number i.
        hr = pCollection->Item(i, &pEndpoint);
        EXIT_ON_ERROR(hr)

                // Get the endpoint ID string.
                hr = pEndpoint->GetId(&pwszID);
        EXIT_ON_ERROR(hr)

                hr = pEndpoint->OpenPropertyStore(STGM_READ, &pProps);
        EXIT_ON_ERROR(hr)

                PROPVARIANT varName;
        // Initialize container for property value.
        PropVariantInit(&varName);

        // Get the endpoint's friendly-name property.
        hr = pProps->GetValue(PKEY_Device_FriendlyName, &varName);//此处可以获得设备名称
        EXIT_ON_ERROR(hr)

        //Print endpoint friendly name and endpoint ID.
        //printf("Endpoint %d: \"%S\" (%S)\n",i, varName.pwszVal, pwszID);
        //qDebug()<<QString :: fromStdWString(varName.pwszVal == nullptr?L"":varName.pwszVal)<<i;
        //qDebug()<<QString :: fromStdWString(pwszID);
        AudioDeviceInfo audioDeviceInfo;
        audioDeviceInfo.name = QString::fromStdWString(varName.pwszVal == nullptr?L"":varName.pwszVal);
        audioDeviceInfo.id = QString::fromStdWString(pwszID == nullptr ? L"" : pwszID);

        if(pwszID != NULL){
            devices.push_back(audioDeviceInfo);
        }

        CoTaskMemFree(pwszID);
        pwszID = NULL;
        PropVariantClear(&varName);
        SAFE_RELEASE(pProps)
                SAFE_RELEASE(pEndpoint)
    }
    SAFE_RELEASE(pEnumerator)
            SAFE_RELEASE(pCollection)
            return true;

Exit:
    printf("Error!\n");
    CoTaskMemFree(pwszID);
    SAFE_RELEASE(pEnumerator)
            SAFE_RELEASE(pCollection)
            SAFE_RELEASE(pEndpoint)
            SAFE_RELEASE(pProps)
            return false;
}
