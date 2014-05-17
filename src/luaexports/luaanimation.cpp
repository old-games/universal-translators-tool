/***************************************************************
 * Name:      luaanimation.cpp
 * Purpose:   lua bindings for Animation
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luaanimation.h"
#include "luacontrol.h"



namespace Lua
{

	void AnimationRegister()
	{
		LUA_REG_CLASS(Animation);
	}

} // namespace Lua



OOLUA_EXPORT_FUNCTIONS(Animation)
OOLUA_EXPORT_FUNCTIONS_CONST(Animation)

