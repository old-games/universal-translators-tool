/***************************************************************
 * Name:      luavideo.cpp
 * Purpose:   lua bindings for Video
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luavideo.h"
#include "luacontrol.h"


DEFINE_EDIT_INFO(editVideo, Video)


namespace Lua
{

	void VideoRegister()
	{
		LUA_REG_CLASS(Video);
		LUA_REG_C_FUNCTION(editVideo);
	}

} // namespace Lua



OOLUA_EXPORT_FUNCTIONS(Video, SetAnimation, SetSound, SetSoundPerFrame)
OOLUA_EXPORT_FUNCTIONS_CONST(Video)

