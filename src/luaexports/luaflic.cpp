/***************************************************************
 * Name:      luaflic.cpp
 * Purpose:   lua bindings for FLIC animation
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luaflic.h"
#include "luacontrol.h"



namespace Lua
{

	void FlicRegister()
	{
		LUA_REG_CLASS(FlicAnimation);
	}

} // namespace Lua



OOLUA_EXPORT_FUNCTIONS(FlicAnimation, OpenFlicFile, AddDynamicChunk)
OOLUA_EXPORT_FUNCTIONS_CONST(FlicAnimation, GetChunksCount, GetChunk,
	GetDynamicChunk)

