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


//OOLUA_CLASS_NO_BASES( Buffer )
//	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
//	OOLUA_NO_TYPEDEFS
//	
//	OOLUA_MEM_FUNC_0(std::string, GetBufferAsString)
//
//	OOLUA_MEM_FUNC_0_CONST( bool, IsOk )
//OOLUA_CLASS_END






#endif // LUABUFFER_H_INCLUDED
