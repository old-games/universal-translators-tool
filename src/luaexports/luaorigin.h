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




OOLUA_CLASS_NO_BASES( Origin )
//	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_CONSTRUCTORS_BEGIN 
	OOLUA_CONSTRUCTOR(Origin::OriginEnum, const char*)
	OOLUA_CONSTRUCTORS_END

	OOLUA_TYPEDEFS Register_class_enums OOLUA_END_TYPES

	OOLUA_ENUMS
		// OriginEnum
		OOLUA_ENUM_ENTRY(Unknown)
		OOLUA_ENUM_ENTRY(FromFile)
		OOLUA_ENUM_ENTRY(FromLibrary)
		OOLUA_ENUM_ENTRY(MaxOrigins)
	OOLUA_ENUMS_END


OOLUA_CLASS_END






#endif // LUAORIGIN_H_INCLUDED
