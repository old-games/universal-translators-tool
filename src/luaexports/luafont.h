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
	OOLUA_TAGS(Shared)

	OOLUA_MFUNC(SetValues)
	OOLUA_MFUNC(AddSymbolFromBuf)
	OOLUA_MFUNC(AddSymbolIndexed)
	OOLUA_MFUNC(SetPalette)
OOLUA_PROXY_END



#endif // LUAFONT_H_INCLUDED
