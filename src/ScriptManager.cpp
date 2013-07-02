#include "ScriptManager.hpp"
#include <SFML/System.hpp>
#include <assert.h>




ScriptManager::ScriptManager()
{
    //ctor
}

ScriptManager::~ScriptManager()
{
    //dtor
}
void ScriptManager::start()
{

}
void ScriptManager::executeScriptFileAtPath(const std::string & filePath)
{
	std::cout << "Do script file: " << filePath << std::endl;
}
