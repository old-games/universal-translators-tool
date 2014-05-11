/***************************************************************
 * Name:      luaorigin.cpp
 * Purpose:   Lua bindings for Origin
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-19
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luaorigin.h"
#include "luacontrol.h"



namespace Lua
{

	void OriginRegister()
	{
		LUA_REG_CLASS(Origin);
	}

}	// namespace Lua




///
/// Экспорт класса Origin
///
OOLUA_EXPORT_FUNCTIONS( Origin )
OOLUA_EXPORT_FUNCTIONS_CONST( Origin, GetFullPath )


