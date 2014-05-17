/***************************************************************
 * Name:      luaanimation.h
 * Purpose:   declaration of lua bindings for Animation
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef __LUA_ANIMAION_H__
#define __LUA_ANIMAION_H__

#include "types/animation.h"
#include "luaiinfo.h"

namespace Lua
{
	void AnimationRegister();
}



OOLUA_PROXY(Animation, IInfo)
	OOLUA_TAGS(Shared)
OOLUA_PROXY_END



#endif // __LUA_ANIMAION_H__
