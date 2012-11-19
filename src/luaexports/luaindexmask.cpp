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
		Get().register_class<IndexMask>();
	}

}   // namespace Lua



///
/// Экспорт класса IndexMask
///
EXPORT_OOLUA_FUNCTIONS_2_NON_CONST( IndexMask, SetMask, IsOk )
EXPORT_OOLUA_FUNCTIONS_0_CONST( IndexMask )

