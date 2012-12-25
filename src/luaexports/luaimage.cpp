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



EXPORT_OOLUA_FUNCTIONS_2_NON_CONST( ImageInfo, SetImage, SetPalette )
EXPORT_OOLUA_FUNCTIONS_1_CONST( ImageInfo, IsOk )


