#pragma once

#include "engine/rendering/Camera.h"

namespace Settings
{
    constexpr int SCR_WIDTH = 1280;
    constexpr int SCR_HEIGHT = 720;
    constexpr double UPDATES_PER_SEC = 60.0; // this doesn't cap the fps, only gamelogic
    constexpr float CAM_FOV = 60.0f;
    constexpr bool CAM_PROJECTION = PROJ_3D;
}
