/***************************************************************
 * Name:      lualibitem.h
 * Purpose:   declaration of lua bindings for LibItem
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-10
 * Copyright: Pavlovets Ilia 2012
 * License:
 **************************************************************/

#ifndef LUALIBITEM_H_INCLUDED
#define LUALIBITEM_H_INCLUDED

#include "types/libtree.h"

namespace Lua
{
	void LibItemRegister();
}



//////////////////////////////////////////////////////////////////////////
// LibItemData class


OOLUA_PROXY(LibItemData)
	OOLUA_MGET(mDataOwner)
	OOLUA_MGET_MSET(mLibFileOffset)
	OOLUA_MGET_MSET(mLibDataSize)
OOLUA_PROXY_END



//////////////////////////////////////////////////////////////////////////
// LibItem class

OOLUA_PROXY(LibItem)
	OOLUA_MFUNC(SetData)
	OOLUA_MEM_FUNC(void, SetText, const char*)
	OOLUA_MFUNC_CONST(IsOk)
	OOLUA_MFUNC_CONST(GetId)
	OOLUA_MFUNC_CONST(GetData)
	OOLUA_MFUNC_CONST(GetChildrenCount)
	OOLUA_MFUNC_CONST(GetChild)
	OOLUA_MEM_FUNC_CONST_RENAME(GetText, std::string, LuaGetText)
OOLUA_PROXY_END

//
//OOLUA_CLASS_NO_BASES( LibItem )
//	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
//	OOLUA_NO_TYPEDEFS
//	
//	OOLUA_MEM_FUNC_1( void, SetData, cpp_in_p<LibItemData*> )
//	//OOLUA_MEM_FUNC_1( void, SetData, LibItemData* )
//	OOLUA_MEM_FUNC_1( void, SetText, const char* )
//	
//	OOLUA_MEM_FUNC_0_CONST( bool, IsOk )
//	OOLUA_MEM_FUNC_0_CONST( LibItemId, GetId )
//	OOLUA_MEM_FUNC_0_CONST( LibItemData*, GetData )
//	OOLUA_MEM_FUNC_0_CONST_RENAME( GetText, std::string, LuaGetText)
//	OOLUA_MEM_FUNC_0_CONST( size_t, GetChildrenCount )
//	OOLUA_MEM_FUNC_1_CONST( LibItem*, GetChild, size_t )
//	
//OOLUA_CLASS_END
//





#endif // LUALIBTREE_H_INCLUDED
