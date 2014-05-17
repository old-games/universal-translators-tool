/***************************************************************
 * Name:      luavideo.h
 * Purpose:   declaration of lua bindings for Video
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef __LUA_VIDEO_H__
#define __LUA_VIDEO_H__

#include "types/video.h"
#include "luaanimation.h"
#include "luasound.h"

namespace Lua
{
	void VideoRegister();
}



OOLUA_PROXY(Video, IInfo)
	OOLUA_TAGS(Shared)

	OOLUA_MFUNC(SetAnimation)
	OOLUA_MFUNC(SetSound)
	OOLUA_MFUNC(SetSoundPerFrame)
OOLUA_PROXY_END



#endif // __LUA_VIDEO_H__
