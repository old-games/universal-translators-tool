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

namespace Lua
{
	void IFFLibRegister();
}




OOLUA_CLASS( IFFLib ) : public Proxy_class< LibTree >
	OOLUA_BASIC

	OOLUA_CONSTRUCTORS_BEGIN 
		OOLUA_CONSTRUCTOR(bool)
	OOLUA_CONSTRUCTORS_END

	OOLUA_NO_TYPEDEFS
	OOLUA_BASES_START LibTree OOLUA_BASES_END

	// bool LoadIFFFile( const char* fileName );	
	OOLUA_MEM_FUNC_1( bool, LoadIFFFile, const char* )

OOLUA_CLASS_END






#endif // LUAFONT_H_INCLUDED
