#include "AnimSpriteComponent.h"

#include <filesystem>
#include <sstream>
#include <stdexcept>

#include "engine/rendering/Renderer.h"
#include "settings.h"

void AnimSpriteComponent::update(const glm::mat4 &parent_transform)
{
    bool render = true;
    m_elapsed_time += Settings::UPDATE_TIME_MS;
    while (m_elapsed_time >= m_frame_factor)
    {
        switch (m_playback_type)
        {
        case PlaybackType::HIDDEN: { render = false; } break;
        case PlaybackType::NOT_PLAYING: break;
        case PlaybackType::ONE_SHOT: 
        {
            if (m_curr_frame < m_frames.size() - 1)
            {
                m_curr_frame++;
                break;
            }
            end_animation();
        } break;
        case PlaybackType::LOOP: 
        {
            m_curr_frame++;
            m_curr_frame = m_curr_frame % (m_frames.size() - 1);
        } break;
        case PlaybackType::BOOMERANG: 
        {
            if (m_curr_frame < m_frames.size() - 1 && m_curr_direction == true)
            {
                m_curr_frame++;
                if (m_curr_frame == m_frames.size() - 1)
                {
                    m_curr_direction = false;
                }
                break;
            }
            else if (m_curr_frame > 0 && m_curr_direction == false)
            {
                m_curr_frame--;
                if (m_curr_frame == 0)
                {
                    m_curr_direction = true;
                }
                break;
            }
        } break;
        case PlaybackType::REVERSE_ONE_SHOT: 
        {
            if (m_curr_frame > 0)
            {
                m_curr_frame--;
                break;
            }
            end_animation();
        } break;
        case PlaybackType::REVERSE_LOOP: 
        {
            if (m_curr_frame > 0)
            {
                m_curr_frame--;
                break;
            }
            m_curr_frame = static_cast<uint32_t>(m_frames.size()) - 1;
        } break;
        }

        m_elapsed_time -= m_frame_factor;
    }
    if (render)
    {
        Renderer::instance().queue_sprite({ *this, transform.get_matrix() * parent_transform });
    }
}

void AnimSpriteComponent::push_folder_as_frames(const std::string &folder)
{
    if (m_frames.size() == 0) { m_playback_type = PlaybackType::NOT_PLAYING; }
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
    if (m_frames.size() == 0) { m_playback_type = PlaybackType::NOT_PLAYING; }
    m_frames.push_back(std::make_shared<Texture>(filepath));
    auto &added_frame = m_frames.at(m_frames.size() - 1);
    m_filter_nearest ? added_frame->filter_nearest() : added_frame->filter_linear();
}

void AnimSpriteComponent::push_frame(std::shared_ptr<Texture> &frame)
{
    if (m_frames.size() == 0) { m_playback_type = PlaybackType::NOT_PLAYING; }
    m_filter_nearest ? frame->filter_nearest() : frame->filter_linear();
    m_frames.push_back(frame);
}

void AnimSpriteComponent::play(PlaybackType type)
{ 
    if (m_frames.size() < 2)
    {
        std::runtime_error("Cannot play an animation with less than two frames.");
    }
    end_animation();
    m_playback_type = type; 

    if (type == PlaybackType::REVERSE_LOOP || type == PlaybackType::REVERSE_ONE_SHOT)
    {
        m_curr_frame = static_cast<uint32_t>(m_frames.size()) - 1;
    }
}

void AnimSpriteComponent::end_animation()
{
    m_playback_type = PlaybackType::NOT_PLAYING;
    switch (m_stop_behavior)
    {
    case StopBehavior::RESET:
        m_curr_frame = 0;
        m_curr_direction = true;
        break;
    case StopBehavior::STAY: break;
    case StopBehavior::END:
        m_curr_frame = static_cast<uint32_t>(m_frames.size()) - 1;
        m_curr_direction = false;
        break;
    }
}

void AnimSpriteComponent::set_frame(uint32_t frame)
{
    assert(!m_frames.empty() && "Cannot access an empty animation");
    const uint32_t position = std::min(static_cast<uint32_t>(m_frames.size() - 1), frame);
    m_curr_frame = position;
}

void AnimSpriteComponent::set_fps(uint32_t new_fps)
{
    m_fps = new_fps;
    m_frame_factor = 1.0 / static_cast<double>(m_fps);
}