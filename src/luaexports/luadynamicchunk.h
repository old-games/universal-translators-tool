/***************************************************************
 * Name:      luadynamicchunk.h
 * Purpose:   declaration of lua bindings for DynamicChunk
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-13
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef __LUA_DYNAMIC_CHUNK_H__
#define __LUA_DYNAMIC_CHUNK_H__

#include "common.h"
#include "luabuffer.h"
#include "types/flicchunks.h"
#include "types/dynamicchunk.h"

namespace Lua
{
	void DynamicChunkRegister();
}


OOLUA_PROXY(FlicChunk)
	OOLUA_TAGS(Abstract, No_default_constructor)
	OOLUA_MFUNC(SetSizeFull)
	OOLUA_MFUNC(LoadData)
	OOLUA_MFUNC_CONST(GetSize)
	OOLUA_MFUNC_CONST(GetType)
	OOLUA_MEM_FUNC_CONST(BufferPtr, GetData)
OOLUA_PROXY_END



OOLUA_PROXY(DataType)
	OOLUA_TAGS(Register_class_enums)

	OOLUA_ENUMS
	(
		OOLUA_ENUM(dtBYTE)
		OOLUA_ENUM(dtCHAR)
		OOLUA_ENUM(dtWORD)
		OOLUA_ENUM(dtSHORT)
		OOLUA_ENUM(dtDWORD)
		OOLUA_ENUM(dtLONG)
		OOLUA_ENUM(dtCUSTOM)
	)
OOLUA_PROXY_END


OOLUA_PROXY(DynamicChunk)
	OOLUA_TAGS(Shared)

	OOLUA_MFUNC(AddValue)
	OOLUA_MFUNC(AddBEValue)
	OOLUA_MFUNC(AddCustomValue)
	OOLUA_MFUNC(SetSizeDependcy)
	OOLUA_MEM_FUNC_CONST_RENAME(GetValue, int, LuaGetValue, const std::string&)
	OOLUA_MFUNC_CONST(GetUnsignedIntValue)
	OOLUA_MFUNC_CONST(GetIntValue)
OOLUA_PROXY_END




OOLUA_PROXY(DynamicFlicChunk, FlicChunk, DynamicChunk)
	OOLUA_TAGS(Shared)
OOLUA_PROXY_END


#endif // __LUA_DYNAMIC_CHUNK_H__
