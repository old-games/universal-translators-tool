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


int	setCurrentPalette(lua_State *L);


namespace Lua
{

void PaletteRegister()
{
	Get().register_class<Palette>();

	LUA_REG_C_FUNCTION( setCurrentPalette );
}

}   // namespace Lua




///
/// Экспорт класса Palette
///
EXPORT_OOLUA_FUNCTIONS_4_NON_CONST( Palette, Initiate, SetCGAType, GetCorrectImageSize, GetPaletteSize )

EXPORT_OOLUA_FUNCTIONS_1_CONST( Palette, IsOk )



int	setCurrentPalette(lua_State *L)
{
	if (Lua::Get().stack_count() != 1)
	{
		wxLogMessage("setCurrentPalette: function need a filled FontInfo table as argument");
		return 0;
	}
	Palette* pal;
	OOLUA::pull2cpp(L, pal);
	
	ChangePaletteEvent palEvent( wxID_ANY, pal, true );
	wxTheApp->ProcessEvent( palEvent );
	return 0;
}