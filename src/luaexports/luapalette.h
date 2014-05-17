/***************************************************************
 * Name:      luapalette.h
 * Purpose:   declaration of lua bindings for Palette
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-14
 * Copyright: Pavlovets Ilia 2012
 * License:
 **************************************************************/

#ifndef __LUA_PALETTE_H__
#define __LUA_PALETTE_H__

#include "types/palette.h"

namespace Lua
{
	void PaletteRegister();
}



OOLUA_PROXY(Palette)
	OOLUA_TAGS(Shared, Register_class_enums)

	OOLUA_ENUMS
	(
		// BPP
		OOLUA_ENUM(bppMono)
		OOLUA_ENUM(bpp2)
		OOLUA_ENUM(bpp4)
		OOLUA_ENUM(bpp8)
		OOLUA_ENUM(bpp15)
		OOLUA_ENUM(bpp16)
		OOLUA_ENUM(bpp24)
		OOLUA_ENUM(bpp32)
		OOLUA_ENUM(bppNum)
		// SourceFormat
		OOLUA_ENUM(sfNone)
		OOLUA_ENUM(sfPlain)
		OOLUA_ENUM(sfBMP)
		OOLUA_ENUM(sfNum)
	)

	OOLUA_MEM_FUNC( bool, Initiate, Palette::BPP, char*,
		Palette::SourceFormat, bool)

	OOLUA_MFUNC(SetCGAType)
	OOLUA_MFUNC_CONST(GetCorrectImageSize)
	OOLUA_MFUNC_CONST(GetPaletteSize)
	OOLUA_MFUNC_CONST(IsOk)

OOLUA_PROXY_END



#endif // __LUA_PALETTE_H__
