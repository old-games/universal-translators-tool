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



OOLUA_PROXY(LibTree, IInfo)
	OOLUA_TAGS(Shared)

	OOLUA_MEM_FUNC(LibItem*, AddItem, LibItem*)
	OOLUA_MFUNC_CONST(FindItem)
	OOLUA_MFUNC_CONST(GetRoot)
OOLUA_PROXY_END



#endif // LUALIBTREE_H_INCLUDED

