/***************************************************************
 * Name:      luaifflib.cpp
 * Purpose:   lua bindings for IFFLib
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-10
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luaifflib.h"
#include "luacontrol.h"



namespace Lua
{

	void IFFLibRegister()
	{
		LUA_REG_CLASS(IFFLib);
	}

}   // namespace Lua




///
/// Экспорт класса IFFLib
///
EXPORT_OOLUA_FUNCTIONS_4_NON_CONST( IFFLib, LoadIFFFile, FindForm, FindChunk, ReadChunkData )

EXPORT_OOLUA_FUNCTIONS_0_CONST( IFFLib )
