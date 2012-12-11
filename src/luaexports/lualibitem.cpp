/***************************************************************
 * Name:      lualibitem.cpp
 * Purpose:   lua bindings for LibItem
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-10
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "lualibitem.h"
#include "luacontrol.h"


namespace Lua
{

	void LibItemRegister()
	{
		LUA_REG_CLASS(LibItem);
	}

}   // namespace Lua




///
/// Экспорт класса LibItem
///
EXPORT_OOLUA_FUNCTIONS_1_NON_CONST( LibItem, AddChild )

EXPORT_OOLUA_FUNCTIONS_1_CONST( LibItem, IsOk )

