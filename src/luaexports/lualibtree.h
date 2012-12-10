/***************************************************************
 * Name:      lualibtree.h
 * Purpose:   declaration of lua bindings for LibTree
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-10
 * Copyright: Pavlovets Ilia 2012
 * License:
 **************************************************************/

#ifndef LUALIBTREE_H_INCLUDED
#define LUALIBTREE_H_INCLUDED

#include "types/libtree.h"
#include "lualibitem.h"

namespace Lua
{
	void LibTreeRegister();
}




OOLUA_CLASS_NO_BASES( LibTree )
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
	OOLUA_NO_TYPEDEFS


	// LibItem*		FindItem( LibItemId itemId );
	OOLUA_MEM_FUNC_1( LibItem*, FindItem, LibItemId )

OOLUA_CLASS_END






#endif // LUALIBTREE_H_INCLUDED
