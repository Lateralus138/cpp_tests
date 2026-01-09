#include "VolumeController.h"
#include <pulse/pulseaudio.h>
#include <stdexcept>
#include <iostream>

class LinuxVolumeController : public IVolumeController {
private:
    pa_mainloop* mainloop_;
    pa_context* context_;
    pa_cvolume current_cvolume_;
    bool is_muted_;
    float current_volume_;

    static void context_state_callback(pa_context* c, void* userdata) {
        auto* self = static_cast<LinuxVolumeController*>(userdata);
        switch (pa_context_get_state(c)) {
            case PA_CONTEXT_READY:
            case PA_CONTEXT_FAILED:
            case PA_CONTEXT_TERMINATED:
                pa_mainloop_get_api(self->mainloop_)->quit(
                    pa_mainloop_get_api(self->mainloop_), 0);
                break;
            default:
                break;
        }
    }

    static void sink_info_callback(pa_context* c, const pa_sink_info* i, int eol, void* userdata) {
        if (!eol && i) {
            auto* self = static_cast<LinuxVolumeController*>(userdata);
            self->current_cvolume_ = i->volume;
            self->is_muted_ = i->mute;
            self->current_volume_ = static_cast<float>(
                pa_cvolume_avg(&i->volume)) / PA_VOLUME_NORM;
        }
    }

public:
    LinuxVolumeController() : mainloop_(nullptr), context_(nullptr), is_muted_(false), current_volume_(0.0f) {
        mainloop_ = pa_mainloop_new();
        if (!mainloop_) {
            throw std::runtime_error("Failed to create PulseAudio mainloop");
        }

        pa_mainloop_api* api = pa_mainloop_get_api(mainloop_);
        context_ = pa_context_new(api, "Volume Control");
        if (!context_) {
            pa_mainloop_free(mainloop_);
            throw std::runtime_error("Failed to create PulseAudio context");
        }

        pa_context_set_state_callback(context_, context_state_callback, this);
        if (pa_context_connect(context_, nullptr, PA_CONTEXT_NOFAIL, nullptr) < 0) {
            pa_context_unref(context_);
            pa_mainloop_free(mainloop_);
            throw std::runtime_error("Failed to connect to PulseAudio");
        }

        // Run mainloop once to connect
        int ret = 0;
        pa_mainloop_iterate(mainloop_, 1, &ret);

        if (pa_context_get_state(context_) != PA_CONTEXT_READY) {
            throw std::runtime_error("Failed to connect to PulseAudio server");
        }

        // Get initial sink info
        pa_operation* op = pa_context_get_sink_info_by_index(context_, 0, sink_info_callback, this);
        while (pa_operation_get_state(op) == PA_OPERATION_RUNNING) {
            pa_mainloop_iterate(mainloop_, 1, &ret);
        }
        pa_operation_unref(op);
    }

    ~LinuxVolumeController() override {
        if (context_) {
            pa_context_disconnect(context_);
            pa_context_unref(context_);
        }
        if (mainloop_) {
            pa_mainloop_free(mainloop_);
        }
    }

    float get_current_volume() override {
        return current_volume_;
    }

    void set_volume(float level) override {
        if (level < 0.0f) level = 0.0f;
        if (level > 1.0f) level = 1.0f;

        pa_volume_t volume = static_cast<pa_volume_t>(level * PA_VOLUME_NORM);
        pa_cvolume_set(&current_cvolume_, current_cvolume_.channels, volume);

        pa_context_set_sink_volume_by_index(context_, 0, &current_cvolume_, nullptr, nullptr);

        int ret = 0;
        while (pa_mainloop_iterate(mainloop_, 0, &ret) > 0) {
            // Process any pending operations
        }

        current_volume_ = level;
    }

    void set_volume_percent(int percent) override {
        set_volume(static_cast<float>(percent) / 100.0f);
    }

    void mute() override {
        pa_context_set_sink_mute_by_index(context_, 0, 1, nullptr, nullptr);
        is_muted_ = true;
        int ret = 0;
        while (pa_mainloop_iterate(mainloop_, 0, &ret) > 0) {}
    }

    void unmute() override {
        pa_context_set_sink_mute_by_index(context_, 0, 0, nullptr, nullptr);
        is_muted_ = false;
        int ret = 0;
        while (pa_mainloop_iterate(mainloop_, 0, &ret) > 0) {}
    }

    bool is_muted() override {
        return is_muted_;
    }

    void set_max_volume() override {
        set_volume(1.0f);
    }

    void set_min_volume() override {
        set_volume(0.0f);
    }
};

std::unique_ptr<IVolumeController> create_volume_controller() {
    return std::make_unique<LinuxVolumeController>();
}