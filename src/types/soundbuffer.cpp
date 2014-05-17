#include "pch.h"
#include "soundbuffer.h"


//bool SoundBuffer::LoadRaw(const wxByte* src, size_t srcSize, unsigned chn,
//	unsigned freq, wxByte xorByte /* 0 */)
//{
//	sf::Int16* data = (sf::Int16*) malloc(srcSize << 1);
//
//#ifndef X64
//	__asm
//	{
//		mov ecx, srcSize
//		mov esi, src
//		mov edi, data
//		mov dl, xorByte
//		cld
//convert_loop:
//			lodsb
//			xor al, dl
//			shl ax, 8
//			stosw
//			dec cx
//		jnz convert_loop
//	}
//#else
//	for (size_t i = 0; i < srcSize; ++i)
//	{
//		sf::Int16& w = data[i];
//		wxByte b = src[i] ^ xorByte;
//		w = b;
//		w <<= 8;
//	}
//#endif
//
//	bool res = this->loadFromSamples(data, srcSize - 1, chn, freq);
//	free(data);
//	return res;
//}


bool SoundBuffer::SaveRawData(wxOutputStream& output)
{
	return IStateStore::SaveData(output, getSamples(), getSampleCount());
}


