/***************************************************************
 * Name:      luasound.cpp
 * Purpose:   lua bindings for Sound
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "luasound.h"
#include "luacontrol.h"


namespace Lua
{

	void SoundRegister()
	{
		LUA_REG_CLASS(sf::SoundBuffer);
		LUA_REG_CLASS(SoundBuffer);
		LUA_REG_CLASS(Sound);
	}

} // namespace Lua


OOLUA_EXPORT_FUNCTIONS(sfSoundBuffer, loadFromFile, loadFromSamples)
OOLUA_EXPORT_FUNCTIONS_CONST(sfSoundBuffer)

OOLUA_EXPORT_FUNCTIONS(SoundBuffer)
OOLUA_EXPORT_FUNCTIONS_CONST(SoundBuffer)

OOLUA_EXPORT_FUNCTIONS(Sound, AddRawData)
OOLUA_EXPORT_FUNCTIONS_CONST(Sound)

