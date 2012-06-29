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

wxWindowID Helpers::wxCustomPanelId = wxID_HIGHEST + 1024;

template<typename T>
void Helpers::CropBuffer(T* dst, int dstWidth, int dstHeight, T* src, int srcWidth, int srcHeight)
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


void Helpers::Buffer8bpp_to_Pixels(Pixel* dst, int dstWidth, int dstHeight, const char* src, int srcWidth, int srcHeight, const Palette& pal )
{
	memset( dst, 0, dstWidth * dstHeight * sizeof( Pixel ) );
	size_t copyLength = sizeof( Pixel ) * dstWidth;
	int correction = srcWidth - dstWidth;
	for (int  y = 0; y < srcHeight; ++y)
	{
		for (int x = 0; x < srcWidth; ++x)
		{
		}
	}
}