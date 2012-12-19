/***************************************************************
 * Name:      luafont.h
 * Purpose:   declaration of lua bindings for font
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-02-09
 * Copyright: Pavlovets Ilia 2012
 * License:
 **************************************************************/

#ifndef LUAFONT_H_INCLUDED
#define LUAFONT_H_INCLUDED

#include "types/fontinfo.h"
#include "gui/fonteditimpl.h"
#include "luapalette.h"
#include "luaorigin.h"
#include "luaindexmask.h"

namespace Lua
{
	void FontRegister();
}



//
//OOLUA_CLASS_NO_BASES( SymbolInfo )
//
//	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
//	OOLUA_NO_TYPEDEFS
//
//	OOLUA_MEM_FUNC_2( RGBA, GetPixel, int, int )
//    OOLUA_MEM_FUNC_3( void, SetPixel, int, int, RGBA )
//	//OOLUA_MEM_FUNC_1( void, SetData, const char* )
//	//OOLUA_MEM_FUNC_4( void, SetValues, int, int, unsigned int, const char*)
//
//OOLUA_CLASS_END






OOLUA_CLASS_NO_BASES( FontInfo )

	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_NO_TYPEDEFS

	OOLUA_MEM_FUNC_8( void, SetValues, int, int, int, int, int, int, int, int)
	OOLUA_MEM_FUNC_5( void, AddSymbolFromBuf, const wxByte*, int, int, int, int )
	OOLUA_MEM_FUNC_3( void, AddSymbolIndexed, IndexMask*, int, int )
	OOLUA_MEM_FUNC_1( bool, SetPalette, Palette* )

	OOLUA_MEM_FUNC_1( void, SetOrigin, const Origin* )
	OOLUA_MEM_FUNC_0_CONST( const Origin*, GetOrigin )

OOLUA_CLASS_END



#endif // LUAFONT_H_INCLUDED
