/***************************************************************
 * Name:      luaindexmask.h
 * Purpose:   declaration of lua bindings for IndexMask
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-18
 * Copyright: Pavlovets Ilia 2012
 * License:
 **************************************************************/

#ifndef LUAINDEXMASK_H_INCLUDED
#define LUAINDEXMASK_H_INCLUDED



#include "types/indexmask.h"
#include "luaiinfo.h"



namespace Lua
{
	void IndexMaskRegister();
}



OOLUA_PROXY(IndexMask, IInfo)
	OOLUA_TAGS(Shared)

	OOLUA_MEM_FUNC( void, SetMask, const char*, int, int, int, int, int )
	OOLUA_MFUNC_CONST(IsOk)
OOLUA_PROXY_END



#endif // LUAINDEXMASK_H_INCLUDED
