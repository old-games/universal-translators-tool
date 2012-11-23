/***************************************************************
 * Name:      luapalette.h
 * Purpose:   declaration of lua bindings for Palette
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-14
 * Copyright: Pavlovets Ilia 2012
 * License:
 **************************************************************/

#ifndef LUAPALETTE_H_INCLUDED
#define LUAPALETTE_H_INCLUDED

#include "types/palette.h"

namespace Lua
{
	void PaletteRegister();
}




OOLUA_CLASS_NO_BASES( Palette )
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR

	OOLUA_TYPEDEFS Register_class_enums OOLUA_END_TYPES

	OOLUA_ENUMS
		// BPP
		OOLUA_ENUM_ENTRY(bppMono)
		OOLUA_ENUM_ENTRY(bpp2)
		OOLUA_ENUM_ENTRY(bpp4)
		OOLUA_ENUM_ENTRY(bpp8)
		OOLUA_ENUM_ENTRY(bpp15)
		OOLUA_ENUM_ENTRY(bpp16)
		OOLUA_ENUM_ENTRY(bpp24)
		OOLUA_ENUM_ENTRY(bpp32)
		OOLUA_ENUM_ENTRY(bppNum)
		// SourceFormat
		OOLUA_ENUM_ENTRY(sfPlain)
		OOLUA_ENUM_ENTRY(sfBMP)
		OOLUA_ENUM_ENTRY(sfNum)
	OOLUA_ENUMS_END


	//	bool		Initiate( BPP bpp, void* src = NULL, SourceFormat fmt = sfPlain, bool shift = false );
	OOLUA_MEM_FUNC_4( bool, Initiate, Palette::BPP, char*, Palette::SourceFormat, bool )

	//	void		SetCGAType( int cga, bool intensity );
	OOLUA_MEM_FUNC_2( void, SetCGAType, int, bool )

	//	unsigned int	GetCorrectImageSize( int width, int height, bool forIndexMask copy );
	OOLUA_MEM_FUNC_3( unsigned int, GetCorrectImageSize, int, int, bool )
	
	//	unsigned int  Palette::GetPaletteSize( BPP bits, SourceFormat fmt )
	OOLUA_MEM_FUNC_2( unsigned int, GetPaletteSize, Palette::BPP, Palette::SourceFormat )
	
	OOLUA_MEM_FUNC_0_CONST( bool, IsOk )
OOLUA_CLASS_END






#endif // LUAFONT_H_INCLUDED
