#pragma once

#include <memory>

class IVolumeController {
public:
    virtual ~IVolumeController() = default;

    virtual float get_current_volume() = 0;
    virtual void set_volume(float level) = 0;
    virtual void set_volume_percent(int percent) = 0;
    virtual void mute() = 0;
    virtual void unmute() = 0;
    virtual bool is_muted() = 0;
    virtual void set_max_volume() = 0;
    virtual void set_min_volume() = 0;
};

// Factory function
std::unique_ptr<IVolumeController> create_volume_controller();