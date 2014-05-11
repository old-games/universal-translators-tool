/***************************************************************
 * Name:      luaindexmask.cpp
 * Purpose:   lua bindings for IndexMask
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-18
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luaindexmask.h"
#include "luacontrol.h"



namespace Lua
{

	void IndexMaskRegister()
	{
		LUA_REG_CLASS(IndexMask);
	}

}   // namespace Lua



///
/// Экспорт класса IndexMask
///
OOLUA_EXPORT_FUNCTIONS(IndexMask, SetMask)
OOLUA_EXPORT_FUNCTIONS_CONST(IndexMask, IsOk)

