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
#include "luaiinfo.h"
#include "luaindexmask.h"



namespace Lua
{
	void FontRegister();
}



OOLUA_PROXY(FontInfo, IInfo)
	OOLUA_MFUNC(SetValues)
	OOLUA_MFUNC(AddSymbolFromBuf)
	OOLUA_MFUNC(AddSymbolIndexed)
	OOLUA_MFUNC(SetPalette)
OOLUA_PROXY_END

//
//OOLUA_CLASS( FontInfo ) : public Proxy_class< IInfo >
//	OOLUA_BASIC
//
//	OOLUA_NO_TYPEDEFS
//	OOLUA_BASES_START IInfo OOLUA_BASES_END
//	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
//
//	OOLUA_MEM_FUNC_8( void, SetValues, int, int, int, int, int, int, int, int)
//	OOLUA_MEM_FUNC_5( void, AddSymbolFromBuf, const wxByte*, int, int, int, int )
//	OOLUA_MEM_FUNC_3( void, AddSymbolIndexed, IndexMask*, int, int )
//	OOLUA_MEM_FUNC_1( bool, SetPalette, Palette* )
//
//OOLUA_CLASS_END



#endif // LUAFONT_H_INCLUDED
