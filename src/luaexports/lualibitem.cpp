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
		LUA_REG_CLASS(LibItemData);
		LUA_REG_CLASS(LibItem);
	}

}   // namespace Lua





///
/// Экспорт класса LibItemData
///
OOLUA_EXPORT_FUNCTIONS(LibItemData, set_mLibFileOffset, set_mLibDataSize)
OOLUA_EXPORT_FUNCTIONS_CONST(LibItemData, get_mDataOwner, get_mLibFileOffset,
								get_mLibDataSize)



//////////////////////////////////////////////////////////////////////////



///
/// Экспорт класса LibItem
///
OOLUA_EXPORT_FUNCTIONS( LibItem, SetData, SetText )
OOLUA_EXPORT_FUNCTIONS_CONST( LibItem, IsOk, GetId, GetData, GetText,
	GetChildrenCount, GetChild )

