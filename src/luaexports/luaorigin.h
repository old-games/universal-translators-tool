/***************************************************************
 * Name:      luaorigin.h
 * Purpose:   declaration of Lua bindings for Origin
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-19
 * Copyright: Pavlovets Ilia 2012
 * License:
 **************************************************************/

#ifndef LUAORIGIN_H_INCLUDED
#define LUAORIGIN_H_INCLUDED

#include "types/origin.h"

namespace Lua
{
	void OriginRegister();
}



OOLUA_PROXY(Origin)
	OOLUA_TAGS(Shared, No_default_constructor, Register_class_enums)

	OOLUA_CTORS
	(
		OOLUA_CTOR(const std::string&)
		OOLUA_CTOR(OriginPtr, wxFileOffset, wxFileOffset)
	)

	OOLUA_ENUMS
	(
		OOLUA_ENUM(Unknown)
		OOLUA_ENUM(FromFile)
		OOLUA_ENUM(FromLibrary)
		OOLUA_ENUM(MaxOrigins)
	)

	OOLUA_MEM_FUNC_CONST_RENAME(GetFullPath, std::string, LuaGetFullPath)

OOLUA_PROXY_END



#endif // LUAORIGIN_H_INCLUDED
