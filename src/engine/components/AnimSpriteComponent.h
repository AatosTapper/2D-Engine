#pragma once

#include "engine/components/SpriteComponent.h"
#include "engine/rendering/Texture.h"

#include <memory>
#include <vector>
#include <string>

class AnimSpriteComponent : public QuadMeshComponent
{
public:
    AnimSpriteComponent(bool pixelated = true) : filter_nearest(pixelated) {}
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
    void stop() { playback_type = PlaybackType::NOT_PLAYING; end_animation(); };
    void hide() { playback_type = PlaybackType::HIDDEN; }

    void set_frame(uint32_t frame);
    void set_fps(uint32_t new_fps);
    void set_stop_behavior(StopBehavior behavior) { stop_behavior = behavior; }

    std::shared_ptr<Texture> get_texture() const override { return frames.at(curr_frame); };

private:
    std::vector<std::shared_ptr<Texture>> frames;
    uint32_t curr_frame{0};
    uint32_t fps{60};
    double frame_factor{1.0 / static_cast<double>(fps)};
    double elapsed_time{0.0f};
    PlaybackType playback_type = PlaybackType::HIDDEN;
    StopBehavior stop_behavior = StopBehavior::RESET;
    bool filter_nearest;
    bool curr_direction{true}; // used for boomerang true: forward, false: backward

    void end_animation();
};
