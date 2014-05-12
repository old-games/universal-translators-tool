/***************************************************************
 * Name:      sound.h
 * Purpose:   base sound class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef __SOUND_H__
#define __SOUND_H__



#include "iinfo.h"


class Sound: public IInfo
{
public:

	Sound();
	Sound(const Sound& other);
	
	virtual ~Sound() = default;
	SoundPtr Clone() const { return std::make_shared<Sound>(*this); }

private:

};



#endif // __SOUND_H__