#pragma once

#include "engine/rendering/Camera.h"
#include "config.h"

namespace Settings
{
    constexpr int SCR_WIDTH = 1280;
    constexpr int SCR_HEIGHT = 720;

    constexpr double UPDATES_PER_SEC = 60.0; // this doesn't cap the fps, only gamelogic
    constexpr double UPDATE_TIME_MS = 1.0 / UPDATES_PER_SEC;
    
    constexpr float CAM_FOV = 30.0f;
    constexpr float CAM_START_DIST = 22.0f;
    constexpr bool CAM_PROJECTION = PROJ_3D;

    constexpr bool HDR = true;

    constexpr uint32_t INITIAL_PHYSICS_ITERATIONS = 16;
    #define PHYSICS_SOLVER_EULER
    #define PHYSICS_SOLVER_RK4
    constexpr float GRAVITY_STRENGTH = 20.0f;
}
