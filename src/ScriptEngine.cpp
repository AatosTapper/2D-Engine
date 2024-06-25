#include "ScriptEngine.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

sol::state ScriptEngine::create_lua_state()
{
    sol::state state;
    state.open_libraries(sol::lib::base);
    return state;
}

void ScriptEngine::run_script(sol::state &lua, const std::string &file_path)
{
    try 
    {
        lua.script_file(file_path);
    }
    catch (const sol::error &e)
    {
        std::cerr << e.what() << "\n\nClosing application with assert" << std::endl;
        assert(false);
    }
}