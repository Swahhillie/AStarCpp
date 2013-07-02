#include "ScriptManager.hpp"
#include <SFML/System.hpp>
#include <assert.h>




ScriptManager::ScriptManager()
:ls(LuaState())
{
    //ctor

}

ScriptManager::~ScriptManager()
{
    //dtor
}
void ScriptManager::start()
{
	luaL_openlibs(ls);
}
void ScriptManager::executeScriptFileAtPath(const char * filePath)
{
	std::cout << "Do script file: " << filePath << std::endl;
	luaL_dofile(ls, filePath);
}
