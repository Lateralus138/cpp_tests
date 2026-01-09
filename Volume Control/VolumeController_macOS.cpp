#include "VolumeController.h"
#include <CoreAudio/CoreAudio.h>
#include <stdexcept>
#include <iostream>

class MacOSVolumeController : public IVolumeController {
private:
    AudioDeviceID device_id_;

    void get_default_output_device() {
        AudioObjectPropertyAddress property_address = {
            kAudioHardwarePropertyDefaultOutputDevice,
            kAudioObjectPropertyScopeGlobal,
            kAudioObjectPropertyElementMaster
        };

        UInt32 data_size = sizeof(device_id_);
        OSStatus status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &property_address,
                                                     0, nullptr, &data_size, &device_id_);

        if (status != noErr) {
            throw std::runtime_error("Failed to get default output device");
        }
    }

public:
    MacOSVolumeController() {
        get_default_output_device();
    }

    ~MacOSVolumeController() override = default;

    float get_current_volume() override {
        AudioObjectPropertyAddress property_address = {
            kAudioDevicePropertyVolumeScalar,
            kAudioDevicePropertyScopeOutput,
            kAudioObjectPropertyElementMaster
        };

        Float32 volume = 0.0f;
        UInt32 data_size = sizeof(volume);
        OSStatus status = AudioObjectGetPropertyData(device_id_, &property_address,
                                                     0, nullptr, &data_size, &volume);

        if (status != noErr) {
            throw std::runtime_error("Failed to get volume");
        }

        return volume;
    }

    void set_volume(float level) override {
        if (level < 0.0f) level = 0.0f;
        if (level > 1.0f) level = 1.0f;

        AudioObjectPropertyAddress property_address = {
            kAudioDevicePropertyVolumeScalar,
            kAudioDevicePropertyScopeOutput,
            kAudioObjectPropertyElementMaster
        };

        Float32 volume = level;
        OSStatus status = AudioObjectSetPropertyData(device_id_, &property_address,
                                                     0, nullptr, sizeof(volume), &volume);

        if (status != noErr) {
            throw std::runtime_error("Failed to set volume");
        }
    }

    void set_volume_percent(int percent) override {
        set_volume(static_cast<float>(percent) / 100.0f);
    }

    void mute() override {
        AudioObjectPropertyAddress property_address = {
            kAudioDevicePropertyMute,
            kAudioDevicePropertyScopeOutput,
            kAudioObjectPropertyElementMaster
        };

        UInt32 mute = 1;
        OSStatus status = AudioObjectSetPropertyData(device_id_, &property_address,
                                                     0, nullptr, sizeof(mute), &mute);

        if (status != noErr) {
            throw std::runtime_error("Failed to mute");
        }
    }

    void unmute() override {
        AudioObjectPropertyAddress property_address = {
            kAudioDevicePropertyMute,
            kAudioDevicePropertyScopeOutput,
            kAudioObjectPropertyElementMaster
        };

        UInt32 mute = 0;
        OSStatus status = AudioObjectSetPropertyData(device_id_, &property_address,
                                                     0, nullptr, sizeof(mute), &mute);

        if (status != noErr) {
            throw std::runtime_error("Failed to unmute");
        }
    }

    bool is_muted() override {
        AudioObjectPropertyAddress property_address = {
            kAudioDevicePropertyMute,
            kAudioDevicePropertyScopeOutput,
            kAudioObjectPropertyElementMaster
        };

        UInt32 mute = 0;
        UInt32 data_size = sizeof(mute);
        OSStatus status = AudioObjectGetPropertyData(device_id_, &property_address,
                                                     0, nullptr, &data_size, &mute);

        if (status != noErr) {
            throw std::runtime_error("Failed to get mute status");
        }

        return mute != 0;
    }

    void set_max_volume() override {
        set_volume(1.0f);
    }

    void set_min_volume() override {
        set_volume(0.0f);
    }
};

std::unique_ptr<IVolumeController> create_volume_controller() {
    return std::make_unique<MacOSVolumeController>();
}