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

}	// namespace Lua




///
/// Экспорт класса IFFLib
///
OOLUA_EXPORT_FUNCTIONS( IFFLib, LoadIFFFile, FindForm, FindChunk, ReadChunkData )
OOLUA_EXPORT_FUNCTIONS_CONST( IFFLib )
