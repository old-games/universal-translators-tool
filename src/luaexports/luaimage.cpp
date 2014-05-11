/***************************************************************
 * Name:      luaimage.cpp
 * Purpose:   lua bindings for Palette
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-19
 * Copyright: Pavlovets Ilia 
 * License:
 **************************************************************/

#include "pch.h"
#include "luaimage.h"
#include "luacontrol.h"



DEFINE_EDIT_INFO(editImage, ImageInfo)



namespace Lua
{

	void ImageInfoRegister()
	{
		LUA_REG_CLASS(ImageInfo);
		LUA_REG_C_FUNCTION( editImage );
	}

}   // namespace Lua




///
/// Экспорт класса ImageInfo
///



OOLUA_EXPORT_FUNCTIONS( ImageInfo, SetImage, SetPalette )
OOLUA_EXPORT_FUNCTIONS_CONST( ImageInfo, IsOk )


