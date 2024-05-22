#pragma once

#include <stdint.h>

// Flags for stuff, represented with each bit being a single flag like this: 0000 0011 0001 1010
// Add new ones like this: NEW_FLAG = LAST_FLAG << 1
// You can combine flags with bitwise OR like this: EntityFlags::NPC | EntityFlags::FRIENDLY | etc

using Bitflag = uint64_t;

enum EntityFlags : Bitflag
{
    PLAYER   = 1u,
    NPC      = PLAYER << 1,
    FRIENDLY = NPC << 1,
    HOSTILE  = FRIENDLY << 1
};

enum EntityStateFlags : Bitflag
{
    ON_GROUND = 1u
};

enum PhysicsFlags : Bitflag
{
    STATIC      = 1u,
    HAS_GRAVITY = STATIC << 1
};