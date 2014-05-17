/***************************************************************
 * Name:      luadynamicchunk.cpp
 * Purpose:   lua bindings for DynamicChunk
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luadynamicchunk.h"
#include "luacontrol.h"



namespace Lua
{

	void DynamicChunkRegister()
	{
		LUA_REG_CLASS(FlicChunk);
		LUA_REG_CLASS(DataType);
		LUA_REG_CLASS(DynamicChunk);
		LUA_REG_CLASS(DynamicFlicChunk);
	}

} // namespace Lua


OOLUA_EXPORT_FUNCTIONS(FlicChunk, SetSizeFull, LoadData)
OOLUA_EXPORT_FUNCTIONS_CONST(FlicChunk, GetSize, GetType, GetData)


OOLUA_EXPORT_NO_FUNCTIONS(DataType)


OOLUA_EXPORT_FUNCTIONS(DynamicChunk, AddValue, AddBEValue, AddCustomValue,
	SetSizeDependcy)
OOLUA_EXPORT_FUNCTIONS_CONST(DynamicChunk, GetValue, GetIntValue,
	GetUnsignedIntValue)


OOLUA_EXPORT_FUNCTIONS(DynamicFlicChunk)
OOLUA_EXPORT_FUNCTIONS_CONST(DynamicFlicChunk)

