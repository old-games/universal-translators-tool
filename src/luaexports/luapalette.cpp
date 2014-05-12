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
		LUA_REG_CLASS(Palette);
		LUA_REG_C_FUNCTION( setCurrentPalette );
	}

} // namespace Lua




///
/// Экспорт класса Palette
///
OOLUA_EXPORT_FUNCTIONS( Palette, Initiate, SetCGAType)
OOLUA_EXPORT_FUNCTIONS_CONST( Palette, IsOk, GetCorrectImageSize, GetPaletteSize)

//EXPORT_OOLUA_FUNCTIONS_4_NON_CONST( Palette, Initiate, SetCGAType, GetCorrectImageSize, GetPaletteSize )
//EXPORT_OOLUA_FUNCTIONS_1_CONST( Palette, IsOk )



int	setCurrentPalette(lua_State *L)
{
	PalettePtr pal = NULL;
	int editorId = -1;

	if (	Lua::Get().stack_count() != 2 || 
			!OOLUA::pull(L, editorId) ||
			!OOLUA::pull(L, pal) )
	{
		wxLogMessage("setCurrentPalette: function need a Palette and editorId as arguments");
		return 0;
	}

	ChangePaletteEvent event( editorId, pal, true );
	wxTheApp->ProcessEvent( event );

	return 0;
}