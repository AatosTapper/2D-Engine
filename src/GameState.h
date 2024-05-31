#pragma once

#include "singleton.h"

// this struct will be saved to a file in the future

struct GlobGameState
{
    IMPL_SINGLETON_DISPATCHER(GlobGameState)
    IMPL_NO_COPY(GlobGameState)

    // data here

private:
    GlobGameState() {}
};
