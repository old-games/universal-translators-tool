/***************************************************************
 * Name:      luaimage.h
 * Purpose:   declaration of lua bindings for ImageInfo
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-19
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef LUAIMAGE_H_INCLUDED
#define LUAIMAGE_H_INCLUDED

#include "types/imageinfo.h"
#include "luapalette.h"
#include "luaindexmask.h"

namespace Lua
{
	void ImageInfoRegister();
}




OOLUA_CLASS_NO_BASES( ImageInfo )
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_NO_TYPEDEFS

	OOLUA_MEM_FUNC_1( void, SetImage, IndexMask* )
	OOLUA_MEM_FUNC_1( bool, SetPalette, Palette* )
	OOLUA_MEM_FUNC_0_CONST( bool, IsOk )

OOLUA_CLASS_END






#endif // LUAIMAGE_H_INCLUDED
