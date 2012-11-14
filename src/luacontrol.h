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

#define LUA_REG_C_FUNCTION(x) lua_register(Lua::Get(), #x, x);

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
