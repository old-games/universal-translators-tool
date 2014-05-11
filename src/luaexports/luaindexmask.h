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
	//OOLUA_MFUNC(SetMask)
	OOLUA_MEM_FUNC( void, SetMask, const char*, int, int, int, int, int )
	OOLUA_MFUNC_CONST(IsOk)
OOLUA_PROXY_END




//OOLUA_CLASS( IndexMask ) : public Proxy_class< IInfo >
//	OOLUA_BASIC
//
//	OOLUA_NO_TYPEDEFS
//	OOLUA_BASES_START IInfo OOLUA_BASES_END
//	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
//
//	//	void SetMask( unsigned char* mask, unsigned size, int width, int height, int srcWidth, int srcHeight );
//	OOLUA_MEM_FUNC_6( void, SetMask, const char*, int, int, int, int, int )
//	OOLUA_MEM_FUNC_0( bool, IsOk )
//OOLUA_CLASS_END






#endif // LUAINDEXMASK_H_INCLUDED
