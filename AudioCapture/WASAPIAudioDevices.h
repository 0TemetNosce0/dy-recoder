#pragma once
#include <QString>
#include <QVector>

struct AudioDeviceInfo {
    QString name;
    QString id;
};

class WASAPIAudioDevices
{
public:
    enum  AudioType{
        AudioInput = 0,
        AudioOut

    };

    explicit WASAPIAudioDevices();
    ~WASAPIAudioDevices();
    static bool GetWASAPIAudioDevices(QVector<AudioDeviceInfo> &devices, bool input);
};


