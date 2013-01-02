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


OOLUA_CLASS_NO_BASES( LibItemData )

	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_NO_TYPEDEFS

	OOLUA_PUBLIC_MEMBER_GET(mDataOwner)
	OOLUA_PUBLIC_MEMBER_GET_SET(mLibFileOffset)
	OOLUA_PUBLIC_MEMBER_GET_SET(mLibDataSize)

OOLUA_CLASS_END



//////////////////////////////////////////////////////////////////////////
// LibItem class


OOLUA_CLASS_NO_BASES( LibItem )
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_NO_TYPEDEFS
	
	// void SetData( LibItemData* data );
	OOLUA_MEM_FUNC_1( void, SetData, cpp_in_p<LibItemData*> )
	OOLUA_MEM_FUNC_1( void, SetText, const char* )

	OOLUA_MEM_FUNC_0_CONST( bool, IsOk )
OOLUA_CLASS_END






#endif // LUALIBTREE_H_INCLUDED
