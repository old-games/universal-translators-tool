/***************************************************************
 * Name:      luafont.cpp
 * Purpose:   lua bindings for font
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-02-09
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luafont.h"
#include "luacontrol.h"


static int editFont(lua_State *L);



namespace Lua
{

void FontRegister()
{
	//Get().register_class<SymbolInfo>();
	Get().register_class<FontInfo>();
	// 
	LUA_REG_C_FUNCTION( editFont );
}

}   // namespace Lua





///
/// Экспорт класса SymbolInfo
///
//EXPORT_OOLUA_FUNCTIONS_2_NON_CONST( SymbolInfo, GetPixel, SetPixel/*, SetData, SetValues*/ )
//EXPORT_OOLUA_FUNCTIONS_0_CONST( SymbolInfo )



///
/// Экспорт класса FontInfo
///
EXPORT_OOLUA_FUNCTIONS_4_NON_CONST( FontInfo, SetValues, AddSymbolFromBuf, AddSymbolIndexed, SetPalette )
EXPORT_OOLUA_FUNCTIONS_0_CONST( FontInfo )



static int editFont(lua_State *L)
{
	if (Lua::Get().stack_count() != 1)
	{
		wxLogMessage("editFont: function need a filled FontInfo table as argument");
		return 0;
	}
	FontInfo* fontInfo;
	OOLUA::pull2cpp(L, fontInfo);
	
	ChangeFontEvent* fontEvent = new ChangeFontEvent( fontInfo );
	wxTheApp->QueueEvent( fontEvent );
	return 0;
}

