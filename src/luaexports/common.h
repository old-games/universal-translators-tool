/***************************************************************
 * Name:      common.h
 * Purpose:   declaration of common functions for Lua
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-02-28
 * Copyright: Pavlovets Ilia 2012 
 * License:
 **************************************************************/

#ifndef LUACOMMON_H_INCLUDED
#define LUACOMMON_H_INCLUDED



namespace Lua
{
	void CommonRegister();
}



OOLUA_PROXY(wxBusyCursor)
OOLUA_PROXY_END




OOLUA_PROXY(wxStreamBase)
	OOLUA_TAGS(Abstract)

	OOLUA_MFUNC_CONST(IsOk)
	OOLUA_MFUNC_CONST(GetSize)

OOLUA_PROXY_END




OOLUA_PROXY(wxInputStream, wxStreamBase)
	OOLUA_TAGS(Abstract)
OOLUA_PROXY_END



OOLUA_PROXY(wxFileInputStream, wxInputStream)
	OOLUA_TAGS(Shared, No_default_constructor)

	OOLUA_CTORS
	(
		OOLUA_CTOR(int)
	)
OOLUA_PROXY_END



#endif // LUAFONT_H_INCLUDED
