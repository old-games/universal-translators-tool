/***************************************************************
 * Name:      luacontrol.h
 * Purpose:   Lua declaration and controls
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-02-08
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef LUACONTROL_H_INCLUDED
#define LUACONTROL_H_INCLUDED

#ifndef RELEASE
	#define REG_MESSAGE(x)	wxLogMessage("Registering "#x); 
#else 
	#define REG_MESSAGE(x)	wxLogDebug("Registering "#x);
#endif

#define LUA_REG_C_FUNCTION(x)	lua_register(Lua::Get(), #x, x); REG_MESSAGE(function #x)
#define LUA_REG_CLASS(x)		Get().register_class<x>(); REG_MESSAGE(class #x)


// macro to create caller to editor
// don't use QueueEvent here! 	
#define DEFINE_EDIT_INFO(funcName, infoName)\
	int funcName(lua_State *L) {	\
	if (Lua::Get().stack_count() != 1)\
		{	wxLogMessage(#funcName": function need a filled "#infoName" class as argument"); return 0; } \
		infoName* info;\
		if ( OOLUA::pull(L, info) )\
		{	ChangeInfoEvent event( info );	\
		wxTheApp->ProcessEvent( event );	} \
		return 0; }



namespace Lua
{
	bool Init();
	void Done();
	inline OOLUA::Script&	Get();
	bool IsOk();

	void ShowLastError();

	void SetRebootFlag();
	bool GetRebootFlag();
}



#endif // LUACONTROL_H_INCLUDED
