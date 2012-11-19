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




namespace Lua
{

void ImageInfoRegister()
{
//	Get().register_class<ImageInfo>();
}

}   // namespace Lua




///
/// Экспорт класса ImageInfo
///
//EXPORT_OOLUA_FUNCTIONS_2_NON_CONST( ImageInfo, Initiate, SetCGAType )

EXPORT_OOLUA_FUNCTIONS_0_CONST( ImageInfo )

