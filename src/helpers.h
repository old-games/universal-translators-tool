/***************************************************************
 * Name:      helpers.h
 * Purpose:   some global functions
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-14
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

namespace Helpers
{

extern wxWindowID wxCustomPanelId;

// копирует буфер в новый с соотвествующими параметрами
// dst должен быть меньше src
// dst на схеме - x
//	xxxooo
//	xxxooo
//	xxxooo
//	oooooo
template<typename T>
void CropBuffer(T* dst, int dstWidth, int dstHeight, T* src, int srcWidth, int srcHeight)
{
	memset( dst, 0, dstWidth * dstHeight * sizeof( T ) );
	size_t copyLength = sizeof( T ) * dstWidth;
	size_t correction = sizeof( T ) * srcWidth - copyLength;
	for (int  y = 0; y < srcHeight; ++y)
	{
		memcpy(dst, src, copyLength);
		src += correction;
	}
}

void Buffer8bpp_to_Pixels(Pixel*dst, int dstWidth, int dstHeight, const char* src, int srcWidth, int srcHeight, const Palette& pal );

} // namespace Helpers


#endif

