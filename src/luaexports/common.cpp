/***************************************************************
 * Name:      common.cpp
 * Purpose:   implementation of common functions for Lua
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-02-28
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luacontrol.h"
#include "common.h"
#include "gui/selmoduleimpl.h"


int reboot( lua_State* )
{
	Lua::SetRebootFlag();
	return 0;
}



int writeToStdCout(lua_State *L)
{
	int n = lua_gettop(L);
	for (int i = 1; i <= n; ++i)
	{
		std::cout << lua_tostring(L, i);
	}
	return 0;
}



int writeToLog(lua_State *L)
{
	int n = lua_gettop(L);
	for (int i = 1; i <= n; ++i)
	{
		wxLogMessage( lua_tostring(L, i) );
	}
	return 0;
}



int parseFileName(lua_State *L)
{
	int n = lua_gettop(L);
	if (n != 1)
	{
		wxLogMessage("parseFileName: function need a string as argument");
		return 0;
	}
	wxString src( lua_tostring(L, 1) );
	wxString volume, path, name, ext;
	wxFileName::SplitPath( src, &volume, &path, &name, &ext );
	volume += wxFileName::GetVolumeSeparator( wxPATH_NATIVE );
	lua_pushstring(L, volume.c_str().AsChar());
	lua_pushstring(L, path.c_str().AsChar());
	lua_pushstring(L, name.c_str().AsChar());
	lua_pushstring(L, ext.c_str().AsChar());
	return 4;
}



int selectModuleDialog(lua_State *L)
{
	int n = lua_gettop(L);

	if (n != 1)
	{
		wxLogMessage("selectModuleDialog: function need a table with module names as argument");
		return 0;
	}

	OOLUA::Lua_table modules;
	OOLUA::pull2cpp(L, modules);
	wxArrayString strings;

	{
		int count = 1;
		std::string value;
		while (modules.safe_at( count++, value ))
		{
			strings.Add( wxString(value) );
		}
	}

	if (strings.size() == 0)
	{
		wxLogMessage("selectModuleDialog: empty table received");
		return 0;
	}

	SelectModuleImpl dlg(NULL);
	dlg.FillCombo( strings );

	wxString result;
	if (dlg.ShowModal() == wxID_OK)
	{
		result = dlg.GetValue();
	}

	lua_pushstring(L, result.c_str().AsChar());
	return 1;
}



//int setPalette(lua_State *L)
//{
//	int stackSize = Lua::Get().stack_count();
//	if (stackSize != 2 && stackSize != 3)
//	{
//		wxLogError("setPalette format: BPP, Palette buffer, [shift values to the left: default is false]");
//		return 0;
//	}
//
//	int bpp = lua_tointeger(L, 1);
//	const char* pal = lua_tostring(L, 2);
//	bool shift = stackSize == 2 ? false : lua_toboolean(L, 3) != 0;
//	ChangePaletteEvent palEvent( bpp, (void*) pal, shift );
//	wxTheApp->QueueEvent( palEvent.Clone() );
//	return 0;
//}



namespace Lua
{

void CommonRegister()
{
    // sets flag to create new Lua VM
	LUA_REG_C_FUNCTION( reboot );

	// writes string to std::cout
	LUA_REG_C_FUNCTION( writeToStdCout );

	// writes string to wxLogMessage
	LUA_REG_C_FUNCTION( writeToLog );

	// parses full filename and returns it's volume, path, name and extension to Lua VM
	LUA_REG_C_FUNCTION( parseFileName );

	// calls dialog to select active plugin
	LUA_REG_C_FUNCTION( selectModuleDialog );

	// export for wxBusyCursor class, will be usefull for continious operations
	Get().register_class<BusyCursor>();
}

} // namespace Lua



EXPORT_OOLUA_NO_FUNCTIONS( BusyCursor )