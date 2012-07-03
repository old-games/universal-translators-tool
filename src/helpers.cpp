/***************************************************************
 * Name:      helpers.cpp
 * Purpose:   Code for helpers 
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-14
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "helpers.h"


namespace Helpers
{

wxWindowID wxCustomPanelId = wxID_HIGHEST + 1024;


void Buffer8bpp_to_Pixels(Pixel* dst, int dstWidth, int dstHeight, const char* src, int srcWidth, int srcHeight, const Palette& pal )
{
	memset( dst, 0, dstWidth * dstHeight * sizeof( Pixel ) );
	size_t copyLength = sizeof( Pixel ) * dstWidth;
	int correction = dstWidth - srcWidth;
	for (int  y = 0; y < srcHeight; ++y)
	{
		for (int x = 0; x < srcWidth; ++x)
		{
			*dst[0] = pal[*src][0];
			*dst[1] = pal[*src][1];
			*dst[2] = pal[*src][2];
			++dst;
			++src;
		}
		dst += correction;
	}
}

} // namespace Helpers