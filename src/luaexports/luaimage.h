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



OOLUA_PROXY(ImageInfo, IInfo)
	OOLUA_TAGS(Shared)

	OOLUA_MFUNC(SetImage)
	OOLUA_MFUNC(SetPalette)
	OOLUA_MFUNC_CONST(IsOk)
OOLUA_PROXY_END



#endif // LUAIMAGE_H_INCLUDED
