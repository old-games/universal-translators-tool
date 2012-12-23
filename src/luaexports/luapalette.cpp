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

}   // namespace Lua




///
/// Экспорт класса Palette
///
EXPORT_OOLUA_FUNCTIONS_4_NON_CONST( Palette, Initiate, SetCGAType, GetCorrectImageSize, GetPaletteSize )

EXPORT_OOLUA_FUNCTIONS_1_CONST( Palette, IsOk )



int	setCurrentPalette(lua_State *L)
{
	Palette* pal = NULL;
	int editorId = -1;

	if (	Lua::Get().stack_count() != 2 || 
			!OOLUA::pull2cpp(L, editorId) ||
			!OOLUA::pull2cpp(L, pal) )
	{
		wxLogMessage("setCurrentPalette: function need a Palette and editorId as arguments");
		return 0;
	}

	ChangePaletteEvent* event = new ChangePaletteEvent( editorId, pal, true );
	wxTheApp->QueueEvent( event );

	return 0;
}