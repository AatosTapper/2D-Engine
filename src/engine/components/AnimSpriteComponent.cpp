#include "AnimSpriteComponent.h"

#include <filesystem>
#include <sstream>
#include <stdexcept>

#include "engine/rendering/Renderer.h"

void AnimSpriteComponent::update(const glm::mat4 &parent_transform)
{
    switch (playback_type)
    {
    case PlaybackType::HIDDEN: return;
    case PlaybackType::NOT_PLAYING: break;
    case PlaybackType::ONE_SHOT: 
    {
        if (curr_frame < frames.size() - 1)
        {
            curr_frame++;
            break;
        }
        end_animation();
    } break;
    case PlaybackType::LOOP: 
    {
        curr_frame++;
        curr_frame = curr_frame % (frames.size() - 1);
    } break;
    case PlaybackType::BOOMERANG: 
    {
        if (curr_frame < frames.size() - 1 && curr_direction == true)
        {
            curr_frame++;
            if (curr_frame == frames.size() - 1)
            {
                curr_direction = false;
            }
            break;
        }
        else if (curr_frame > 0 && curr_direction == false)
        {
            curr_frame--;
            if (curr_frame == 0)
            {
                curr_direction = true;
            }
            break;
        }
    } break;
    case PlaybackType::REVERSE_ONE_SHOT: 
    {
        if (curr_frame > 0)
        {
            curr_frame--;
            break;
        }
        end_animation();
    } break;
    case PlaybackType::REVERSE_LOOP: 
    {
        if (curr_frame > 0)
        {
            curr_frame--;
            break;
        }
        curr_frame = static_cast<uint32_t>(frames.size()) - 1;
    } break;
    }

    Renderer::instance().queue_sprite({ *this, transform.get_matrix() * parent_transform });
}

void AnimSpriteComponent::push_folder_as_frames(const std::string &folder)
{
    if (frames.size() == 0) { playback_type = PlaybackType::NOT_PLAYING; }
    // find how many frames are stored in the directory
    auto dir_iter = std::filesystem::directory_iterator(folder);
    uint32_t file_count = 0;
    for (auto& entry : dir_iter)
    {
        if (is_regular_file(entry.path()))
        {
            file_count++;
        }
    }

    std::stringstream filenameStream;
    for (uint32_t i = 0; i < file_count; i++)
    {
        filenameStream.str("");
        if (folder.at(folder.size() - 1) == '/')
        {
            filenameStream << folder << "frame" << i + 1 << ".png";
        }
        else
        {
            filenameStream << folder << "/frame" << i + 1 << ".png";
        }
        
        push_frame(filenameStream.str());
    }
}

void AnimSpriteComponent::push_frame(const std::string &filepath)
{
    if (frames.size() == 0) { playback_type = PlaybackType::NOT_PLAYING; }
    frames.push_back(std::make_shared<Texture>(filepath));
    auto &added_frame = frames.at(frames.size() - 1);
    filter_nearest ? added_frame->filter_nearest() : added_frame->filter_linear();
}

void AnimSpriteComponent::push_frame(std::shared_ptr<Texture> &frame)
{
    if (frames.size() == 0) { playback_type = PlaybackType::NOT_PLAYING; }
    filter_nearest ? frame->filter_nearest() : frame->filter_linear();
    frames.push_back(frame);
}

void AnimSpriteComponent::play(PlaybackType type)
{ 
    if (frames.size() < 2)
    {
        std::runtime_error("Cannot play an animation with less than two frames.");
    }
    end_animation();
    playback_type = type; 

    if (type == PlaybackType::REVERSE_LOOP || type == PlaybackType::REVERSE_ONE_SHOT)
    {
        curr_frame = static_cast<uint32_t>(frames.size()) - 1;
    }
}

void AnimSpriteComponent::end_animation()
{
    playback_type = PlaybackType::NOT_PLAYING;
    switch (stop_behavior)
    {
    case StopBehavior::RESET:
        curr_frame = 0;
        curr_direction = true;
        break;
    case StopBehavior::STAY: break;
    case StopBehavior::END:
        curr_frame = static_cast<uint32_t>(frames.size()) - 1;
        curr_direction = false;
        break;
    }
}
