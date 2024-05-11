#pragma once

#include "engine/rendering/Camera.h"
#include "config.h"

namespace Settings
{
    constexpr int SCR_WIDTH = 1280;
    constexpr int SCR_HEIGHT = 720;

    constexpr double UPDATES_PER_SEC = 60.0; // this doesn't cap the fps, only gamelogic
    
    constexpr float CAM_FOV = 60.0f;
    constexpr bool CAM_PROJECTION = PROJ_3D;

    constexpr bool HDR = true;
    constexpr glm::vec3 BG_COL = { 0.0f, 0.0f, 0.0f };
}
