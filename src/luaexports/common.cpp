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



/**
\brief From LuaVM: reboot()
Включает флаг перезагрузки виртуальной машины Lua::SetRebootFlag()
\return nil
*/
int reboot( lua_State* )
{
	Lua::SetRebootFlag();
	return 0;
}



/**
\brief From LuaVM: writeToStdCout(...)
Запись строк в std::cout.
\param string, string, string ... строки в любом количестве
\return nil
*/
int writeToStdCout(lua_State *L)
{
	int n = lua_gettop(L);
	for (int i = 1; i <= n; ++i)
	{
		std::cout << lua_tostring(L, i);
	}
	return 0;
}



/**
\brief From LuaVM: writeToLog(...)
Запись строк в лог.
\param string, string, string ... строки в любом количестве
\return nil
*/
int writeToLog(lua_State *L)
{
	int n = lua_gettop(L);
	for (int i = 1; i <= n; ++i)
	{
		wxLogMessage( lua_tostring(L, i) );
	}
	return 0;
}



/**
\brief From LuaVM: parseFileName(string)
Функция разделяет имя файла на составные части.
\param string - полное имя файла
\return string, string, string - путь, имя, расширение
*/
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



/// \brief Внутренняя функция, считывает из стека LuaVM массив строк и предлагает выбрать одну из них.
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



/**
\brief From LuaVM: selectModuleDialog(string[])
Открывает диалог выбора модуля игры.
\param string[] - массив строк - названий модулей
\return string - выбранный модуль или пустую строку, если пользователь отменил действие.
*/
int selectModuleDialog(lua_State *L)
{
	return selectSomething( L );
}



/**
\brief From LuaVM: selectVersionDialog(string[])
Открывает диалог выбора версии игры.
\param string[] - массив строк - версий игры
\return string - выбранную версию или пустую строку, если пользователь отменил действие.
*/
int selectVersionDialog(lua_State *L)
{
	return selectSomething( L, "Select game version" );
}



/**
\brief From LuaVM: saveFileDialog(string = "Any file (*.*)|*.*")
Открывает диалог выбора файла для записи.
\param string - список расширений формата
\return string - полный путь к файлу или nil, если пользователь отменил действие
*/
int selectFromList(lua_State *L)
{
	return selectSomething( L, "Select" );
}



//////////////////////////////////////////////////////////////////////////



#define FILEDIALOG_BODY(txt, flags) \
	std::string extensions;\
	if ( !OOLUA::pull(L, extensions) )\
	{	extensions = "Any file (*.*)|*.*";	}\
	wxFileDialog dlg( NULL, txt, wxEmptyString, wxEmptyString, extensions, flags );\
	if (dlg.ShowModal() != wxID_OK)\
	{		return 0;	}\
	OOLUA::push(L, dlg.GetPath().ToStdString());\
	return 1;\



/**
\brief From LuaVM: openFileDialog(string = "Any file (*.*)|*.*")
Открывает диалог выбора файла для чтения.
\param string - список расширений формата
\return string - полный путь к файлу или nil, если пользователь отменил действие
*/
int openFileDialog(lua_State *L)
{
	FILEDIALOG_BODY("Open file...", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
}



/**
\brief From LuaVM: saveFileDialog(string = "Any file (*.*)|*.*")
Открывает диалог выбора файла для записи.
\param string - список расширений формата
\return string - полный путь к файлу или nil, если пользователь отменил действие
*/
int saveFileDialog(lua_State *L)
{
	FILEDIALOG_BODY("Save file...", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
}

#undef FILEDIALOG_BODY



//////////////////////////////////////////////////////////////////////////



/**
\brief From LuaVM: setModuleReady()
Создаёт событие, об завершении инициации модуля.
\return nil
*/
int setModuleReady(lua_State* L)
{
	L; // to remove warning of unused variable
	CommonEvent event;
	wxTheApp->QueueEvent( event.Clone() );
	return 0;
}


/// Внутренняя функция, используется при изменении параметров проекта.
int createCommonEvent(lua_State* L, CommonEvent::CommoneEventOperation op)
{
	CommonEvent event(op);
	wxArrayString values;
	Helpers::PullStringArguments(values, L);
	wxASSERT(values.size() == 2);
	event.AddParam(values[0]);
	event.AddParam(values[1]);
	wxTheApp->ProcessEvent(event);
	return 0;
}



/**
\brief From LuaVM: setProjectName(string, string)
Создаёт событие, об изменении имени и рабочего пути проекта.
\param string - имя проекта
\param string - каталог проекта
\return nil
*/
int setProjectName(lua_State* L)
{
	return createCommonEvent(L, CommonEvent::ceSetProjectName);
}



/**
\brief From LuaVM: setProjectPath(string, string)
Создаёт событие, об изменении пути к игре и последнего активного каталога в каком-либо диалоге.
\param string - путь к игре
\param string - путь, который будет использоваться каким-либо диалогом.
\return nil
*/
int setProjectPath(lua_State* L)
{
	return createCommonEvent(L, CommonEvent::ceSetProjectPath);
}



/**
\brief From LuaVM: setProjectModule(string, string)
Создаёт событие, об изменении модуля и версии модуля.
\param string - имя модуля (определено в initmodule.lua: local ModuleName)
\param string - версия игры
\return nil
*/
int setProjectModule(lua_State* L)
{
	return createCommonEvent(L, CommonEvent::ceSetProjectModule);
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



/**
\brief From LuaVM: getStrInt(string, int)
Функция возвращает байт строки.
\param string - строка(буфер)
\param int - смещение [0..#string) (C style)
\return unsigned char (Lua's int)
*/
int getStrInt(lua_State *L)
{
	GET_BUFNINDEX(getStrInt)
	lua_pushnumber(L, buf[i]);
	return 1;
}



/**
\brief From LuaVM: getStrChar(string, int)
Функция возвращает символ строки.
\param string - строка(буфер)
\param int - смещение [0..#string) (C style)
\return string
*/
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



/**
\brief From LuaVM: strToChar(string), strToShort(string), strToInt(string)
Функция возвращает целочисленное значение со знаком из буфера.
Для ускорения выполнения функция делает минимальную проверку на корректность буфера.
\param string - строка - буфер двоичных данных
\return int, но не более стандартных размеров для char, short и int
*/
template<typename T>
int strToSigned(lua_State *L)
{
	GET_BYTES_BUFFER(strToSigned);
	lua_pushinteger(L, (T&) *buf);
	return 1;
}



/**
\brief From LuaVM: strToByte(string), strToWord(string), strToUint(string)
Функция возвращает целочисленное значение без знака из буфера.
Для ускорения выполнения функция делает минимальную проверку на корректность буфера.
\param string - строка - буфер двоичных данных
\return int, но не более стандартных размеров для unsigned: char, short и int
*/
template<typename T>
int strToUnsigned(lua_State *L)
{
	GET_BYTES_BUFFER(strToUnsigned);
	lua_pushunsigned(L, (T&) *buf);
	return 1;
}


#undef GET_BYTES_BUFFER



//////////////////////////////////////////////////////////////////////////



/**
\brief From LuaVM: swap16(int)
Функция меняет порядок байтов в shortint
\param int - целое число 16bit
\return int
*/
int swap16(lua_State *L)
{
	wxUint16 value;
	if (OOLUA::pull( L, value ))
	{
		Helpers::SwapEndian16( value );
		OOLUA::push( L, value );
		return 1;
	}
	return 0;
}




/**
\brief From LuaVM: swap32(int)
Функция меняет порядок байтов в int
\param int - целое число 32bit
\return int
*/
int swap32(lua_State *L)
{
	wxUint32 value;
	if (OOLUA::pull( L, value ))
	{
		Helpers::SwapEndian32( value );
		OOLUA::push( L, value );
		return 1;
	}
	return 0;
}



/**
\brief From LuaVM: swap64(int)
Функция меняет порядок байтов в shortint
\param int - целое число 64bit
\return int
*/
int swap64(lua_State *L)
{
	wxUint64 value;
	if (OOLUA::pull( L, value ))
	{
		Helpers::SwapEndian64( value );
		OOLUA::push( L, value );
		return 1;
	}
	return 0;
}



//////////////////////////////////////////////////////////////////////////



/**
\brief From LuaVM: swapStringBytes(string srcBuffer, int position1, int position2, int quantity)
Функция меняет местами байты в буфере
Пример использования можно видеть в tie.lua - LoadStarwarsFont
\param string - входящий буфер (не изменяется в процессе выполнения)
\param int - первая позиция в буфере
\param int - вторая позиция в буфере
\param int - количество байт для изменения
\return string - изменённый буфер
*/
int swapStringBytes(lua_State *L)
{
	std::string	src;
	int pos1 = 0;
	int pos2 = 0;
	int quantity = 0;

	if (!OOLUA::pull( L, quantity ) ||
		!OOLUA::pull( L, pos2 ) ||
		!OOLUA::pull( L, pos1 ) ||
		!OOLUA::pull( L, src ) )
	{
		wxLogError("swapStringBytes: function need arguments (string, position 1, position 2, quantity");
		return 0;
	}

	std::string result( src.c_str(), src.length() );

	int pos1count = pos1;
	int pos2count = pos2;

	for (int i = 0; i < quantity; ++i)
	{
		result[pos1count] = src[pos2count];
		result[pos2count] = src[pos1count];
		++pos1count;
		++pos2count;
	}

	lua_pushlstring(L, result.c_str(), result.length());
	return 1;
}



//////////////////////////////////////////////////////////////////////////



// Lua's string.sub can't iterate through buffer with zero character
// this function is to avoid it
// extractBuffer( string, from, to = length of string )

// upd: this is wrong, sub is doing all right, TODO: delete it?

//int extractBuffer(lua_State *L)
//{
//	std::string buf;
//	size_t from = 0;
//	size_t to = 0;
//
//	bool correctCall = false;
//	if (lua_gettop(L) == 2)
//	{
//		correctCall = OOLUA::pull2cpp(L, from) && OOLUA::pull2cpp(L, buf);
//		to = buf.length();
//	}
//	else
//	{
//		if (lua_gettop(L) == 3)
//		{
//			correctCall = OOLUA::pull2cpp(L, to) && OOLUA::pull2cpp(L, from) &&	OOLUA::pull2cpp(L, buf);
//		}
//	}
//
//	if (!correctCall || to < from)
//	{
//		wxLogError("extractBuffer call format: (string, from, to = length of string");
//		return 0;
//	}
//
//	size_t len = to - from;
//	char* res = (char*) malloc(len);
//
//	memcpy(res, buf.c_str() + from, len);
//	lua_pushlstring (L, res, len);
//	free(res);
//
//	return 1;
//}



//////////////////////////////////////////////////////////////////////////



/**
\brief From LuaVM: messageBox(string)
Функция вызывает wxMessageBox, показывает любое сообщение пользователю.
\param string - информация для пользователя
\return nil
*/
int messageBox(lua_State *L)
{
	std::string s;

	if (OOLUA::pull( L, s ))
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

	// creates event to set project's parameters
	LUA_REG_C_FUNCTION( setProjectName );
	LUA_REG_C_FUNCTION( setProjectModule );
	LUA_REG_C_FUNCTION( setProjectPath );

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

	// swap bytes in buffer
	LUA_REG_C_FUNCTION( swapStringBytes );

	//LUA_REG_C_FUNCTION( extractBuffer );

	// calls MessageBox to show important messages to user
	LUA_REG_C_FUNCTION( messageBox );

	// calls wxFileDialog
	LUA_REG_C_FUNCTION( openFileDialog );
	LUA_REG_C_FUNCTION( saveFileDialog );

	// export for wxBusyCursor class, will be usefull for continious operations
	Get().register_class<wxBusyCursor>();

	RegisterBitwiseFunctions();
	RegisterRLEFunctions();
}

} // namespace Lua



OOLUA_EXPORT_NO_FUNCTIONS( wxBusyCursor )
