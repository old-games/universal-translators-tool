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


int editImage(lua_State *L);

namespace Lua
{

void ImageInfoRegister()
{
	Get().register_class<ImageInfo>();
	LUA_REG_C_FUNCTION( editImage );
}

}   // namespace Lua




///
/// Экспорт класса ImageInfo
///



EXPORT_OOLUA_FUNCTIONS_2_NON_CONST( ImageInfo, SetImage, SetPalette )
EXPORT_OOLUA_FUNCTIONS_0_CONST( ImageInfo )



int editImage(lua_State *L)
{
	if (Lua::Get().stack_count() != 1)
	{
		wxLogMessage("editImage: function need a filled ImageInfo class as argument");
		return 0;
	}
	ImageInfo* imageInfo;
	OOLUA::pull2cpp(L, imageInfo);
	
	ChangeImageEvent* imageEvent = new ChangeImageEvent( imageInfo );
	wxTheApp->QueueEvent( imageEvent );
	return 0;
}
