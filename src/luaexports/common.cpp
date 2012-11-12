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
#include "gui/selmoduleimpl.h"


static int reboot( lua_State* )
{
	Lua::SetRebootFlag();
	return 0;
}

static int writeToStdCout(lua_State *L)
{
	int n = lua_gettop(L);
	for (int i = 1; i <= n; ++i)
	{
		std::cout << lua_tostring(L, i);
	}
	return 0;
}

static int writeToLog(lua_State *L)
{
	int n = lua_gettop(L);
	for (int i = 1; i <= n; ++i)
	{
		wxLogMessage( lua_tostring(L, i) );
	}
	return 0;
}

static int parseFileName(lua_State *L)
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
	lua_pushstring(L, volume.c_str().AsChar());
	lua_pushstring(L, path.c_str().AsChar());
	lua_pushstring(L, name.c_str().AsChar());
	lua_pushstring(L, ext.c_str().AsChar());
	return 4;
}

static int selectModuleDialog(lua_State *L)
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

namespace Lua
{

void CommonRegister()
{
    // sets flag to create new Lua VM
	lua_register(Lua::Get(), "reboot", reboot);

	// writes string to std::cout
	lua_register(Lua::Get(), "writeToStdCout", writeToStdCout);

	// writes string to wxLogMessage
	lua_register(Lua::Get(), "writeToLog", writeToLog);

	// parses full filename and returns it's volume, path, name and extension to Lua VM
	lua_register(Lua::Get(), "parseFileName", parseFileName);

	// calls dialog to select active plugin
	lua_register(Lua::Get(), "selectModuleDialog", selectModuleDialog);
}

} // namespace Lua
