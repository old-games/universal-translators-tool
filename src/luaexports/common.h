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



class BusyCursor
{
public:
	BusyCursor(): mBusy( new wxBusyCursor() ) {}
	~BusyCursor() { delete mBusy; }
private: 
	wxBusyCursor*	mBusy;
};




OOLUA_CLASS_NO_BASES( BusyCursor )
    OOLUA_NO_TYPEDEFS
    OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END


#endif // LUAFONT_H_INCLUDED
