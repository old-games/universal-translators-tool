/***************************************************************
 * Name:      luapalette.cpp
 * Purpose:   lua bindings for Palette
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-14
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luapalette.h"
#include "luacontrol.h"




namespace Lua
{

void PaletteRegister()
{
	Get().register_class<Palette>();
}

}   // namespace Lua




///
/// Экспорт класса Palette
///
EXPORT_OOLUA_FUNCTIONS_4_NON_CONST( Palette, Initiate, SetCGAType, GetCorrectImageSize, GetPaletteSize )

EXPORT_OOLUA_FUNCTIONS_1_CONST( Palette, IsOk )

