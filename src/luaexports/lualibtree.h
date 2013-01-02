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
#include "luaiinfo.h"

namespace Lua
{
	void LibTreeRegister();
}




OOLUA_CLASS( LibTree ) : public Proxy_class< IInfo >
	OOLUA_BASIC

	OOLUA_NO_TYPEDEFS
	OOLUA_BASES_START IInfo OOLUA_BASES_END
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR


	// LibItem*	AddItem( LibItem* parent = NULL );
	OOLUA_MEM_FUNC_1( LibItem*, AddItem, LibItem* )
	
	// LibItem*		FindItem( LibItemId itemId );
	OOLUA_MEM_FUNC_1_CONST( LibItem*, FindItem, LibItemId )
	
	// LibItem*		GetRoot();
	OOLUA_MEM_FUNC_0_CONST( LibItem*, GetRoot )

OOLUA_CLASS_END






#endif // LUALIBTREE_H_INCLUDED
