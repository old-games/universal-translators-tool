/***************************************************************
 * Name:      luaflic.h
 * Purpose:   declaration of lua bindings for FLIC animation
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef __LUA_FLIC_H__
#define __LUA_FLIC_H__



#include "types/flic.h"
#include "luaanimation.h"
#include "luadynamicchunk.h"



namespace Lua
{
	void FlicRegister();
}



OOLUA_PROXY(FlicAnimation, Animation)
	OOLUA_TAGS(Shared)

	OOLUA_MFUNC(OpenFlicFile)
	OOLUA_MFUNC(AddDynamicChunk)
	OOLUA_MFUNC_CONST(GetChunksCount)
	OOLUA_MFUNC_CONST(GetChunk)
	OOLUA_MFUNC_CONST(GetDynamicChunk)
OOLUA_PROXY_END



#endif // __LUA_FLIC_H__
