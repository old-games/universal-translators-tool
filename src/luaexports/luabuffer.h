/***************************************************************
 * Name:      luabuffer.h
 * Purpose:   declaration of lua bindings for Buffer
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-12
 * Copyright: Pavlovets Ilia 2012
 * License:
 **************************************************************/

#ifndef LUABUFFER_H_INCLUDED
#define LUABUFFER_H_INCLUDED

#include "types/buffer.h"



namespace Lua
{
	void BufferRegister();
}


OOLUA_PROXY(Buffer)
	OOLUA_MFUNC(GetBufferAsString)
	OOLUA_MFUNC_CONST(IsOk)
OOLUA_PROXY_END


#endif // LUABUFFER_H_INCLUDED
