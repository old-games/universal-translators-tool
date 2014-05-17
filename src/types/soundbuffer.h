#ifndef __SOUND_BUFFER_H__
#define __SOUND_BUFFER_H__



#include "buffer.h"



class SoundBuffer: public sf::SoundBuffer
{
public:


//	bool LoadRaw(const wxByte* src, size_t srcSize, unsigned chn, unsigned freq,
//		wxByte xorByte = 0);
	bool SaveRawData(wxOutputStream& output);

private:
};



#endif // __SOUND_BUFFER_H__