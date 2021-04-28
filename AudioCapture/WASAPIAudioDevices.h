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
    explicit WASAPIAudioDevices();
    ~WASAPIAudioDevices();
    bool GetWASAPIAudioDevices(QVector<AudioDeviceInfo> &devices, bool input);
};


