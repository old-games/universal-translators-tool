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





DEFINE_EDIT_INFO(editLibrary, LibTree)



namespace Lua
{

	void LibTreeRegister()
	{
		LUA_REG_CLASS(LibTree);
		LUA_REG_C_FUNCTION(editLibrary);
	}

}	// namespace Lua




///
/// Экспорт класса LibTree
///
OOLUA_EXPORT_FUNCTIONS( LibTree, AddItem )
OOLUA_EXPORT_FUNCTIONS_CONST( LibTree, FindItem, GetRoot )



