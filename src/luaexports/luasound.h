/***************************************************************
 * Name:      luasound.h
 * Purpose:   declaration of lua bindings for Sound
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef __LUA_SOUND_H__
#define __LUA_SOUND_H__

#include "types/sound.h"
#include "types/soundbuffer.h"
#include "luaiinfo.h"
#include "luabuffer.h"

namespace Lua
{
	void SoundRegister();
}


namespace OOLUA
{
	typedef sf::SoundBuffer sfSoundBuffer;
}	// OOLUA


OOLUA_PROXY(sfSoundBuffer)
	OOLUA_TAGS(Shared)

	OOLUA_MFUNC(loadFromFile)
	OOLUA_MFUNC(loadFromSamples)
OOLUA_PROXY_END


OOLUA_PROXY(SoundBuffer)
	OOLUA_TAGS(Shared)

	//OOLUA_MFUNC(loadFromFile)
	//OOLUA_MFUNC(loadFromSamples)
OOLUA_PROXY_END


OOLUA_PROXY(Sound, IInfo)
	OOLUA_TAGS(Shared)

	OOLUA_CTORS
	(
		OOLUA_CTOR(unsigned, unsigned)
	)

	OOLUA_MFUNC(AddRawData)
OOLUA_PROXY_END



#endif // __LUA_SOUND_H__
