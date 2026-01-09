#include "VolumeController.h"
#include <endpointvolume.h>
#include <mmdeviceapi.h>
#include <windows.h>

#ifdef OPTIONAL
#undef OPTIONAL
#endif

#pragma comment(lib, "ole32.lib")

class WindowsVolumeController : public IVolumeController {
private:
    IMMDeviceEnumerator* enumerator_;
    IMMDevice* device_;
    IAudioEndpointVolume* volume_;

public:
    WindowsVolumeController() : enumerator_(nullptr), device_(nullptr), volume_(nullptr) {
        CoInitialize(nullptr);

        CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
            __uuidof(IMMDeviceEnumerator), (void**)&enumerator_);

        enumerator_->GetDefaultAudioEndpoint(eRender, eConsole, &device_);

        device_->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr,
            (void**)&volume_);
    }

    ~WindowsVolumeController() override {
        if (volume_) volume_->Release();
        if (device_) device_->Release();
        if (enumerator_) enumerator_->Release();
        CoUninitialize();
    }

    float get_current_volume() override {
        float current_volume;
        volume_->GetMasterVolumeLevelScalar(&current_volume);
        return current_volume;
    }

    void set_volume(float level) override {
        if (level < 0.0f) level = 0.0f;
        if (level > 1.0f) level = 1.0f;
        volume_->SetMasterVolumeLevelScalar(level, nullptr);
    }

    void set_volume_percent(int percent) override {
        float level = static_cast<float>(percent) / 100.0f;
        set_volume(level);
    }

    void mute() override {
        volume_->SetMute(TRUE, nullptr);
    }

    void unmute() override {
        volume_->SetMute(FALSE, nullptr);
    }

    bool is_muted() override {
        BOOL is_muted;
        volume_->GetMute(&is_muted);
        return is_muted == TRUE;
    }

    void set_max_volume() override {
        set_volume(1.0f);
    }

    void set_min_volume() override {
        set_volume(0.0f);
    }
};

std::unique_ptr<IVolumeController> create_volume_controller() {
    return std::make_unique<WindowsVolumeController>();
}