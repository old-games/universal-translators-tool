/***************************************************************
 * Name:      lualibtree.cpp
 * Purpose:   lua bindings for LibTree
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-10
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "lualibtree.h"
#include "luacontrol.h"


namespace Lua
{

	void LibTreeRegister()
	{
		LUA_REG_CLASS(LibTree);
	}

}   // namespace Lua




///
/// Экспорт класса LibTree
///
EXPORT_OOLUA_FUNCTIONS_1_NON_CONST( LibTree, FindItem )

EXPORT_OOLUA_FUNCTIONS_0_CONST( LibTree )

