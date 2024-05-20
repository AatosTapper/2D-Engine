#pragma once

#include "engine/components/SpriteComponent.h"
#include "engine/rendering/Texture.h"

#include <memory>
#include <vector>
#include <string>

class AnimSpriteComponent : public QuadMeshComponent
{
public:
    AnimSpriteComponent(bool pixelated = true) : m_filter_nearest(pixelated) {}
    ~AnimSpriteComponent() override {}

    enum class PlaybackType  : uint8_t
    {
        HIDDEN,
        NOT_PLAYING,
        ONE_SHOT,           // play once and stop
        LOOP,               // play continuously until someone calls stop()
        BOOMERANG,          // same as LOOP but every other time is reversed
        REVERSE_ONE_SHOT,   // same as ONE_SHOT but reverse
        REVERSE_LOOP        // same as LOOP but reverse
    };

    enum class StopBehavior : uint8_t
    {
        RESET,              // return back to the first frame
        STAY,               // stay where stopped
        END                 // jump to the last frame even if stopped in the middle
    };

    void update(const glm::mat4 &parent_transform); // call every frame in update_components() function

    // Pass in a folder that contains all of the animation images. (It also can't have anything else)
    // The images must be named like this: frame1.png, frame2.png ... frame194.png
    void push_folder_as_frames(const std::string &folder);

    void push_frame(const std::string &filepath);
    void push_frame(std::shared_ptr<Texture> &frame);

    void play(PlaybackType type);
    void stop() { m_playback_type = PlaybackType::NOT_PLAYING; end_animation(); };
    void hide() { m_playback_type = PlaybackType::HIDDEN; }

    void set_frame(uint32_t frame);
    void set_fps(uint32_t new_fps);
    void set_stop_behavior(StopBehavior behavior) { m_stop_behavior = behavior; }

    std::shared_ptr<Texture> get_texture() const override { return m_frames.at(m_curr_frame); };

private:
    std::vector<std::shared_ptr<Texture>> m_frames;
    uint32_t m_curr_frame = 0;
    uint32_t m_fps = 60;
    double m_frame_factor = 1.0 / static_cast<double>(m_fps);
    double m_elapsed_time = 0.0f;
    PlaybackType m_playback_type = PlaybackType::HIDDEN;
    StopBehavior m_stop_behavior = StopBehavior::RESET;
    bool m_filter_nearest;
    bool m_curr_direction = true; // used for boomerang true: forward, false: backward

    void end_animation();
};
