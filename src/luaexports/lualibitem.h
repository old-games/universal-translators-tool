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




OOLUA_CLASS_NO_BASES( LibItem )
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_NO_TYPEDEFS
	
	// LibItem* AddChild();
	OOLUA_MEM_FUNC_0( LibItem*, AddChild )

	OOLUA_MEM_FUNC_0_CONST( bool, IsOk )
OOLUA_CLASS_END






#endif // LUALIBTREE_H_INCLUDED
