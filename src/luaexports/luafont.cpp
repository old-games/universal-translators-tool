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



DEFINE_EDIT_INFO(editFont, FontInfo)



namespace Lua
{

	void FontRegister()
	{
		LUA_REG_CLASS(FontInfo);
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



EXPORT_OOLUA_FUNCTIONS_4_NON_CONST( FontInfo, SetValues, AddSymbolFromBuf, 
								   AddSymbolIndexed, SetPalette )
EXPORT_OOLUA_FUNCTIONS_0_CONST( FontInfo )


