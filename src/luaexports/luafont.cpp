/***************************************************************
 * Name:      luafont.cpp
 * Purpose:   lua bindings for font
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-02-09
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
//#include "fontinfo.h"
//#include "gui/fonteditimpl.h"

#include "luafont.h"
#include "luacontrol.h"


static int editFont(lua_State *L);



namespace Lua
{

void FontRegister()
{
	Get().register_class<RGBA>();
	Get().register_class<SymbolInfo>();
	Get().register_class<FontInfo>();
	// 
	LUA_REG_C_FUNCTION( editFont );
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
/// Экспорт класса SymbolInfo
///
EXPORT_OOLUA_FUNCTIONS_2_NON_CONST( SymbolInfo, GetPixel, SetPixel/*, SetData, SetValues*/ )
EXPORT_OOLUA_FUNCTIONS_0_CONST( SymbolInfo )



///
/// Экспорт класса FontInfo
///
EXPORT_OOLUA_FUNCTIONS_3_NON_CONST( FontInfo, SetValues, AddSymbol, SetPalette )
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
	
	ChangeFontEvent* fontEvent = new ChangeFontEvent( fontInfo->Clone() );
	wxTheApp->QueueEvent( fontEvent );
	return 0;
}

