#pragma once

#include "engine/components/SpriteComponent.h"
#include "engine/rendering/Texture.h"

#include <memory>
#include <vector>
#include <string>

class AnimSpriteComponent : public QuadMesh
{
public:
    ~AnimSpriteComponent() override {}

    enum class PlaybackType : uint8_t
    {
        NOT_PLAYING,
        ONE_SHOT,           // play once and stop
        LOOP,               // play continuously until someone calls stop()
        BOOMERANG,          // same as LOOP but every other time is reversed
        REVERSE_ONE_SHOT,   // same as ONE_SHOT but reverse
        REVERSE_LOOP        // same as LOOP but reverse
    };

    void update(); // call every frame in update_components() function

    void add_frames(const std::string &folder); // the frames need to be named in a certain way
    void push_frame(const std::string &filepath);
    void push_frame(Texture &frame);

    void play(PlaybackType type);
    void stop();

private:
    std::vector<Texture> frames;
    uint32_t curr_frame{};
    PlaybackType playback_type = PlaybackType::NOT_PLAYING;
};