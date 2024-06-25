#pragma once

#include <string>
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include "singleton.h"

class ScriptEngine
{
public:
    IMPL_NO_COPY(ScriptEngine)

    static sol::state create_lua_state();
    static void run_script(sol::state &lua, const std::string &file_path);

private:
    ScriptEngine() = delete;
};