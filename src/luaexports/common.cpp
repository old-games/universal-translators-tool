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



int selectSomething(lua_State *L, const wxString& title = wxEmptyString)
{
	if (lua_gettop(L) != 1)
	{
		wxLogError("selectDialog: function need a table with module names as argument");
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
		wxLogError("selectDialog: empty table received");
		return 0;
	}

	SelectModuleImpl dlg(NULL);
	
	if (!title.IsEmpty())
	{
		dlg.SetTitle( title );
	}

	dlg.FillCombo( strings );

	wxString result;
	if (dlg.ShowModal() == wxID_OK)
	{
		result = dlg.GetValue();
	}

	lua_pushstring(L, result.c_str().AsChar());
	return 1;
}



int selectModuleDialog(lua_State *L)
{
	return selectSomething( L );
}



int selectVersionDialog(lua_State *L)
{
	return selectSomething( L, "Select game version" );
}



int setModuleReady(lua_State* L)
{
	L; // to remove warning of unused variable
	ModuleChangedEvent event;
	wxTheApp->QueueEvent( event.Clone() );	
	return 0;
}



int convertBufferToChar(lua_State* L)
{
	unsigned int size = 0;
	int bitCount = 0;
	std::string s;
	if ( lua_gettop(L) != 3 || 
		!OOLUA::pull2cpp(L, bitCount) || 
		!OOLUA::pull2cpp(L, size) || 
		!OOLUA::pull2cpp(L, s))
	{
		wxLogError("convertBuffer: function need a size and source buffer and source bit count");
		return 0;
	}

	const char* src = s.c_str();
	unsigned int dev = 8 / bitCount;
	unsigned int destSize = size * dev;
	char* res = (char*) malloc( destSize );

	char bitMask = 1;
	for (int i = 1; i < bitCount; ++i)
	{
		bitMask <<= 1;
		bitMask |= 1;
	}

	unsigned char* dest = (unsigned char*) res;
	for (size_t i = 0; i < size; ++i)
	{
		dest += dev;
		for (size_t part = 0; part < dev; ++part)
		{
			--dest;
			const unsigned char shift = part * bitCount;
			*dest = (src[i] & (bitMask << shift) ) >> shift;
		}
		dest += dev;
	}

	lua_pushlstring (L, res, destSize);
	OOLUA::push2lua(L, destSize);
	free(res);
	return 2;
}




#define GET_BUFNINDEX(x)	\
	if (lua_gettop(L) != 2)	{ \
		wxLogError(#x": function need a string and number of a value in array"); \
		return 0;	} \
	const char* buf = lua_tostring(L, 1); \
	int i = lua_tointeger(L, 2); \
	lua_pop(L, 2); \
	if (!buf) { return 0; }




int getStrInt(lua_State *L)
{
	GET_BUFNINDEX(getStrInt)
	lua_pushnumber(L, buf[i]);
	return 1;
}



int getStrChar(lua_State *L)
{
	GET_BUFNINDEX(getStrChar)
	lua_pushlstring(L, &buf[i], 1);
	return 1;
}

#undef GET_BUFNINDEX



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

	// calls dialog to select game version
	LUA_REG_C_FUNCTION( selectVersionDialog );

	// creates event about changed module
	LUA_REG_C_FUNCTION( setModuleReady );

	// returns buffer converted to bitcount
	LUA_REG_C_FUNCTION( convertBufferToChar );

	// returns buffer value at position, "getString(bytes, 3)" for example returns fourth value
	// this function IS NOT SAFE
	LUA_REG_C_FUNCTION( getStrInt );
	LUA_REG_C_FUNCTION( getStrChar );

	// export for wxBusyCursor class, will be usefull for continious operations
	Get().register_class<BusyCursor>();
}

} // namespace Lua



EXPORT_OOLUA_NO_FUNCTIONS( BusyCursor )