/***************************************************************
 * Name:      luaiinfo.cpp
 * Purpose:   lua bindings for IInfo
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-23
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luaiinfo.h"
#include "luacontrol.h"


namespace Lua
{

	void IInfoRegister()
	{
		LUA_REG_CLASS(IInfo);
	}

}	// namespace Lua



///
/// Экспорт класса IInfo
///


OOLUA_EXPORT_FUNCTIONS( IInfo, SetOrigin )
OOLUA_EXPORT_FUNCTIONS_CONST( IInfo, GetOrigin )


