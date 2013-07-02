#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP

#include "Manager.hpp"
#include <sstream>
#include <cstdio>
#include "LuaState.hpp"


class ScriptManager : public Manager
{
	public:
		static ScriptManager & instance()
		{
			static ScriptManager INSTANCE;
			return INSTANCE;
		}
		virtual ~ScriptManager();

		void executeScriptFileAtPath(const char * filePath);
	protected:
		virtual void start();
	private:
		ScriptManager();

		LuaState ls;

};

#endif // SCRIPTMANAGER_HPP
