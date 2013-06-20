#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP

#include "Manager.hpp"
#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include <sstream>
#include <cstdio>


class ScriptManager : public Manager
{
	public:
		static ScriptManager & instance()
		{
			static ScriptManager INSTANCE;
			return INSTANCE;
		}
		virtual ~ScriptManager();
	protected:
		virtual void start();
	private:
		ScriptManager();

		asIScriptEngine * engine_;

		void buildScripts();
		void runScripts();

		//registering types

		void registerVector3();
};

#endif // SCRIPTMANAGER_HPP
