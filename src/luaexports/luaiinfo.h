/***************************************************************
 * Name:      luaiinfo.h
 * Purpose:   declaration of lua bindings for IInfo
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-23
 * Copyright: Pavlovets Ilia 2012
 * License:
 **************************************************************/

#ifndef LUAIINFO_H_INCLUDED
#define LUAIINFO_H_INCLUDED

#include "types/iinfo.h"
#include "luaorigin.h"

namespace Lua
{
	void IInfoRegister();
}


OOLUA_PROXY(IInfo)
	OOLUA_TAGS(Abstract)

	OOLUA_MFUNC(SetOrigin)
	OOLUA_MFUNC_CONST(GetOrigin)
OOLUA_PROXY_END



#endif // LUAIINFO_H_INCLUDED
