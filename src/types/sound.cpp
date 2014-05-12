#include "pch.h"
#include "sound.h"


const wxString	SOUNDNAME = "Sound";
const int		SOUNDVERSION = 0x100;



Sound::Sound():
	IInfo( SOUNDNAME, SOUNDVERSION, etSound)
{
}



Sound::Sound(const Sound& other):
	IInfo(other)
{
}

