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
#include "algs/bitwise.h"
#include "algs/rle.h"

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
	wxString path, name, ext;
	wxFileName::SplitPath( src, &path, &name, &ext );
	//volume += wxFileName::GetVolumeSeparator( wxPATH_NATIVE );
	//lua_pushstring(L, volume.c_str().AsChar());
	lua_pushstring(L, path.c_str().AsChar());
	lua_pushstring(L, name.c_str().AsChar());
	lua_pushstring(L, ext.c_str().AsChar());
	return 3;
}



int selectSomething(lua_State *L, const wxString& title = wxEmptyString)
{
	if (lua_gettop(L) != 1)
	{
		wxLogError("selectDialog: function need a table with module names as argument");
		return 0;
	}

	wxArrayString strings;
	Helpers::PullTableOfStrings( strings, L );
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



int selectFromList(lua_State *L)
{
	return selectSomething( L, "Select" );
}


//////////////////////////////////////////////////////////////////////////



#define FILEDIALOG_BODY(txt, flags) \
	std::string extensions;\
	if ( !OOLUA::pull2cpp(L, extensions) )\
	{	extensions = "Any file (*.*)|*.*";	}\
	wxFileDialog dlg( NULL, txt, wxEmptyString, wxEmptyString, extensions, flags );\
	if (dlg.ShowModal() != wxID_OK)\
	{		return 0;	}\
	OOLUA::push2lua(L, dlg.GetPath().ToStdString());\
	return 1;\


int openFileDialog(lua_State *L)
{
	FILEDIALOG_BODY("Open file...", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	//std::string extensions;
	//if ( !OOLUA::pull2cpp(L, extensions) )
	//{
	//	extensions = "Any file (*.*)|*.*";
	//}


	//wxFileDialog dlg( NULL, "Open file...", wxEmptyString, wxEmptyString, extensions, wxFD_OPEN|wxFD_FILE_MUST_EXIST );
	//if (dlg.ShowModal() != wxID_OK)
	//{
	//	return 0;
	//}

	//OOLUA::push2lua(L, dlg.GetPath().ToStdString());

	//return 1;
}



int saveFileDialog(lua_State *L)
{
	FILEDIALOG_BODY("Save file...", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
}

#undef FILEDIALOG_BODY



//////////////////////////////////////////////////////////////////////////



int setModuleReady(lua_State* L)
{
	L; // to remove warning of unused variable
	ModuleChangedEvent event;
	wxTheApp->QueueEvent( event.Clone() );	
	return 0;
}



//////////////////////////////////////////////////////////////////////////



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



//////////////////////////////////////////////////////////////////////////



#ifndef RELEASE
	#define CHECK_STR_TO_(x) \
		if (lua_gettop(L) != 1)	\
		{ \
			wxLogError(#x": function need a buffer as argument"); \
			return 0;	\
		} 
#else
	#define CHECK_STR_TO_(x)
#endif


#define GET_BYTES_BUFFER(x) CHECK_STR_TO_(x)\
	const char* buf = lua_tostring(L, 1); \
	lua_pop(L, 1); \
	if (!buf) { return 0; }

template<typename T>
int strToSigned(lua_State *L)
{
	GET_BYTES_BUFFER(strToSigned);
	lua_pushinteger(L, (T&) *buf);
	return 1;
}


template<typename T>
int strToUnsigned(lua_State *L)
{
	GET_BYTES_BUFFER(strToUnsigned);
	lua_pushunsigned(L, (T&) *buf);
	return 1;
}


#undef GET_BYTES_BUFFER



//////////////////////////////////////////////////////////////////////////



int swap16(lua_State *L)
{
	wxUint16 value;
	if (OOLUA::pull2cpp( L, value ))
	{
		Helpers::SwapEndian16( value );
		OOLUA::push2lua( L, value );
		return 1;
	}
	return 0;
}



int swap32(lua_State *L)
{
	wxUint32 value;
	if (OOLUA::pull2cpp( L, value ))
	{
		Helpers::SwapEndian32( value );
		OOLUA::push2lua( L, value );
		return 1;
	}
	return 0;
}


int swap64(lua_State *L)
{
	wxUint64 value;
	if (OOLUA::pull2cpp( L, value ))
	{
		Helpers::SwapEndian64( value );
		OOLUA::push2lua( L, value );
		return 1;
	}
	return 0;
}



//////////////////////////////////////////////////////////////////////////

// Lua's string.sub can't iterate through buffer with zero character 
// this function is to avoid it
// extractBuffer( string, from, to = length of string )
int extractBuffer(lua_State *L)
{
	std::string buf;
	size_t from = 0;
	size_t to = 0;

	bool correctCall = false;
	if (lua_gettop(L) == 2)
	{
		correctCall = OOLUA::pull2cpp(L, from) && OOLUA::pull2cpp(L, buf);
		to = buf.length();
	}
	else
	{
		if (lua_gettop(L) == 3)
		{
			correctCall = OOLUA::pull2cpp(L, to) && OOLUA::pull2cpp(L, from) &&	OOLUA::pull2cpp(L, buf);
		}
	}

	if (!correctCall || to < from)
	{
		wxLogError("extractBuffer call format: (string, from, to = length of string");
		return 0;
	}

	size_t len = to - from;
	char* res = (char*) malloc(len);

	memcpy(res, buf.c_str() + from, len);
	lua_pushlstring (L, res, len);
	free(res);

	return 1;
}



//////////////////////////////////////////////////////////////////////////




int messageBox(lua_State *L)
{
	std::string s;
	if (OOLUA::pull2cpp( L, s ))
	{
		wxMessageBox( s, "Module information" );
	}
	return 0;
}



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

	// selects anything from any list
	LUA_REG_C_FUNCTION( selectFromList );

	// creates event about changed module
	LUA_REG_C_FUNCTION( setModuleReady );

	// returns buffer value at position, "getString(bytes, 3)" for example returns fourth value
	// this function IS NOT SAFE
	LUA_REG_C_FUNCTION( getStrInt );
	LUA_REG_C_FUNCTION( getStrChar );

	// these functions are to convert bytes buffer to integer values
	lua_register(Lua::Get(), "strToChar", strToSigned<wxInt8>);
	lua_register(Lua::Get(), "strToShort", strToSigned<wxInt16>);
	lua_register(Lua::Get(), "strToInt", strToSigned<wxInt32>);

	lua_register(Lua::Get(), "strToByte", strToUnsigned<wxUint8>);
	lua_register(Lua::Get(), "strToWord", strToUnsigned<wxUint16>);
	lua_register(Lua::Get(), "strToUint", strToUnsigned<wxUint32>);

	// swap integer endian
	LUA_REG_C_FUNCTION( swap16 );
	LUA_REG_C_FUNCTION( swap32 );
	LUA_REG_C_FUNCTION( swap64 );

	LUA_REG_C_FUNCTION( extractBuffer );
	
	// calls MessageBox to show important messages to user
	LUA_REG_C_FUNCTION( messageBox );

	// calls wxFileDialog 
	LUA_REG_C_FUNCTION( openFileDialog );
	LUA_REG_C_FUNCTION( saveFileDialog );

	// export for wxBusyCursor class, will be usefull for continious operations
	Get().register_class<BusyCursor>();

	RegisterBitwiseFunctions();
	RegisterRLEFunctions();
}

} // namespace Lua



EXPORT_OOLUA_NO_FUNCTIONS( BusyCursor )