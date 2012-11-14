/***************************************************************
 * Name:      fontinfo.cpp
 * Purpose:   FontInfo used to store information about font
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-07-02
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "fontinfo.h"


SymbolInfo FontInfo::sBadSymbol;



void FontInfo::SetValues( int maxWidth, int maxHeight, int minWidth, int minHeight,
				int bpp /* BPP::bppMono */,
				int fontCodePage /* wxFONTENCODING_DEFAULT */,
				int baseLine /* 0 */,
				int capLine /* 0 */,
				int lowLine /* 0 */)
{
	mMaxWidth = maxWidth;
	mMaxHeight = maxHeight;
	mMinWidth = minWidth;
	mMinHeight = minHeight;
	mBPP = bpp;
	mFontCodePage = fontCodePage;
	mBaseLine = baseLine;
	mCapLine = capLine;
	mLowLine = lowLine;
}



size_t FontInfo::GetSymbolsNum()
{
	return mSymbols.size();
}


void FontInfo::SetSymbolsNum(size_t n)
{
	if (n >= MINIMUM_SYMBOLS_NUM)
	{
		mSymbols.resize(n);
	}
}



SymbolInfo& FontInfo::GetSymbol(size_t n)
{
	if ( n < mSymbols.size() )
	{
		return mSymbols[n];
	}
	return sBadSymbol;
}



void FontInfo::AddSymbol( const char* data, int width, int height )
{
	SymbolInfo info;
	LetterBox box;
	Helpers::Buffer8bpp_to_Pixels( (Pixel*) &box, MAXIMUM_SYMBOL_WIDTH, MAXIMUM_SYMBOL_HEIGHT, data, width, height, mPalette );
	info.SetValues( width, height, mSymbols.size(), &box );
	mSymbols.push_back( info );
}



void FontInfo::SetPalette(const char* src, bool shift)
{
	wxASSERT( sizeof(mPalette) <= BPP::PaletteSize( mBPP ) );
	memcpy( &mPalette, src, BPP::PaletteSize( mBPP ) );

	if (shift)
	{
		for (size_t i = 0; i < sizeof(mPalette) / sizeof(mPalette[0]); ++i)
		{
			mPalette[i][0] <<= 2;
			mPalette[i][1] <<= 2;
			mPalette[i][2] <<= 2;
		}
	}
}