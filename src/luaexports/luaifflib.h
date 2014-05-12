/***************************************************************
 * Name:      luaifflib.h
 * Purpose:   declaration of lua bindings for IFFLib
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-10
 * Copyright: Pavlovets Ilia 2012
 * License:
 **************************************************************/

#ifndef LUAIFFLIB_H_INCLUDED
#define LUAIFFLIB_H_INCLUDED



#include "types/ifflib.h"
#include "lualibtree.h"
#include "luabuffer.h"



namespace Lua
{
	void IFFLibRegister();
}



OOLUA_PROXY(IFFLib, LibTree)
	OOLUA_TAGS(Shared, No_default_constructor)

	OOLUA_CTORS
	(
		OOLUA_CTOR(bool)
	)

	OOLUA_MEM_FUNC(bool, LoadIFFFile, const char*)
	OOLUA_MFUNC(FindForm)
	OOLUA_MFUNC(FindSubForm)
	OOLUA_MFUNC(FindChunk)
	OOLUA_MEM_FUNC(std::string, ReadChunkData, LibItem*)
OOLUA_PROXY_END



#endif // LUAFONT_H_INCLUDED
