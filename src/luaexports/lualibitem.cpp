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
EXPORT_OOLUA_FUNCTIONS_2_NON_CONST(LibItemData,
								   set_mLibFileOffset,
								   set_mLibDataSize)

EXPORT_OOLUA_FUNCTIONS_3_CONST(LibItemData,
								   get_mDataOwner,
								   get_mLibFileOffset,
								   get_mLibDataSize)



//////////////////////////////////////////////////////////////////////////



///
/// Экспорт класса LibItem
///
EXPORT_OOLUA_FUNCTIONS_2_NON_CONST( LibItem, SetData, SetText )

EXPORT_OOLUA_FUNCTIONS_1_CONST( LibItem, IsOk )

