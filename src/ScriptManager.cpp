#include "ScriptManager.hpp"
#include <SFML/System.hpp>
#include <assert.h>
#include <scriptarray/scriptarray.h>

void MessageCallback(const asSMessageInfo * msg, void * param)
{
	const char * type = "ERR ";
	if(msg->type == asMSGTYPE_WARNING )
		type = "WARN";
	else if(msg->type == asMSGTYPE_INFORMATION)
		type = "INFO";

	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}
void print(std::string & msg)
{
	printf("%s", msg.c_str());
}



ScriptManager::ScriptManager():
    engine_(nullptr)
{
    //ctor
}

ScriptManager::~ScriptManager()
{
    //dtor
    engine_->Release();
}
void ScriptManager::start()
{
    assert(engine_ == nullptr);
    engine_ = asCreateScriptEngine(ANGELSCRIPT_VERSION);
    int r = engine_->SetMessageCallback(asFUNCTION(MessageCallback), nullptr, asCALL_CDECL);
    assert(r >= 0);

    RegisterStdString(engine_);

    r = engine_->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
    assert(r >= 0);
    buildScripts();
    RegisterScriptArray(engine_, true);
    runScripts();
}
void ScriptManager::buildScripts()
{
    assert(engine_ != nullptr);

    CScriptBuilder builder;
    int r = builder.StartNewModule(engine_, "BasicModule");
    if( r < 0 )
    {
        // If the code fails here it is usually because there
        // is no more memory to allocate the module
        printf("Unrecoverable error while starting a new module.\n");
        return;
    }
    r = builder.AddSectionFromFile("test.as");
    if( r < 0 )
    {
        // The builder wasn't able to load the file. Maybe the file
        // has been removed, or the wrong name was given, or some
        // preprocessing commands are incorrectly written.
        printf("Please correct the errors in the script and try again.\n");
        return;
    }
    r = builder.BuildModule();
    if( r < 0 )
    {
        // An error occurred. Instruct the script writer to fix the
        // compilation errors that were listed in the output stream.
        printf("Please correct the errors in the script and try again.\n");
        return;
    }

}

void ScriptManager::runScripts()
{
	 // Find the function that is to be called.
    assert(engine_ != nullptr);

    asIScriptModule *mod = engine_->GetModule("BasicModule");
    asIScriptFunction *func = mod->GetFunctionByDecl("void main()");
    if( func == 0 )
    {
        // The function couldn't be found. Instruct the script writer
        // to include the expected function in the script.
        printf("The script must have the function 'void main()'. Please add it and try again.\n");
        return;
    }
// Create our context, prepare it, and then execute
    asIScriptContext *ctx = engine_->CreateContext();
    ctx->Prepare(func);
	int r = ctx->Execute();
    if( r != asEXECUTION_FINISHED )
    {
        // The execution didn't complete as expected. Determine what happened.
        if( r == asEXECUTION_EXCEPTION )
        {
            // An exception occurred, let the script writer know what happened so it can be corrected.
            printf("An exception '%s' occurred. Please correct the code and try again.\n", ctx->GetExceptionString());
        }
    }
    ctx->Release();
}

