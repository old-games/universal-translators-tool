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


static int editFont(lua_State *L);



namespace Lua
{

void PaletteRegister()
{
	Get().register_class<RGBA>();
	Get().register_class<Palette>();
}

}   // namespace Lua




//
//	Экспорт класса RGBA
//
EXPORT_OOLUA_FUNCTIONS_4_NON_CONST(RGBA,
								   set_R,
								   set_G,
								   set_B,
								   set_A)

EXPORT_OOLUA_FUNCTIONS_4_CONST(RGBA,
							   get_R,
							   get_G,
							   get_B,
							   get_A)


///
/// Экспорт класса Palette
///
EXPORT_OOLUA_FUNCTIONS_2_NON_CONST( Palette, Initiate, SetCGAType )

EXPORT_OOLUA_FUNCTIONS_0_CONST( Palette )

