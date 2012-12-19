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

}   // namespace Lua




///
/// Экспорт класса Origin
///
EXPORT_OOLUA_FUNCTIONS_0_NON_CONST( Origin )

EXPORT_OOLUA_FUNCTIONS_0_CONST( Origin )


