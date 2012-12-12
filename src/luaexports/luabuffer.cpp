/***************************************************************
 * Name:      luabuffer.cpp
 * Purpose:   lua bindings for Buffer
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luabuffer.h"
#include "luacontrol.h"


namespace Lua
{

	void BufferRegister()
	{
		LUA_REG_CLASS(Buffer);
	}

}   // namespace Lua




///
/// Экспорт класса LibItem
///
EXPORT_OOLUA_FUNCTIONS_1_NON_CONST( Buffer, GetBufferAsString )

EXPORT_OOLUA_FUNCTIONS_1_CONST( Buffer, IsOk )

