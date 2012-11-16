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
#include "palette.h"

SymbolInfo FontInfo::sBadSymbol;


FontInfo::FontInfo():
	mMaxHeight( 0 ),
	mMinHeight( 0 ),
	mMaxWidth( 0 ),
	mMinWidth( 0 ),
	mBaseLine( 0 ),
	mCapLine( 0 ),
	mLowLine( 0 ),
	mBPP( Palette::bppMono ),
	mFontCodePage( 0 ),
	mPalette( NULL )
{
}

FontInfo::FontInfo( const FontInfo& other ):
	mMaxHeight( other.mMaxHeight ),
	mMinHeight( other.mMinHeight ),
	mMaxWidth( other.mMaxWidth ),
	mMinWidth( other.mMinWidth ),
	mBaseLine( other.mBaseLine ),
	mCapLine( other.mCapLine ),
	mLowLine( other.mLowLine ),
	mBPP( other.mBPP ),
	mFontCodePage( other.mFontCodePage ),
	mSymbols( other.mSymbols ),
	mPalette( NULL )
{
	if (other.mPalette)
	{
		mPalette = other.mPalette->Clone();
	}
}

FontInfo::~FontInfo()
{
	ClearPalette();
}


void FontInfo::SetValues( int maxWidth, int maxHeight, int minWidth, int minHeight,
				int fontCodePage /* wxFONTENCODING_DEFAULT */,
				int baseLine /* 0 */,
				int capLine /* 0 */,
				int lowLine /* 0 */)
{
	mMaxWidth = maxWidth;
	mMaxHeight = maxHeight;
	mMinWidth = minWidth;
	mMinHeight = minHeight;
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



void FontInfo::AddSymbol( const char* data, int width, int height, int swidth, int sheight )
{
	SymbolInfo info;
	LetterBox box;
	Helpers::Buffer8bpp_to_Pixels( (Pixel*) &box, MAXIMUM_SYMBOL_WIDTH, MAXIMUM_SYMBOL_HEIGHT, data, mMaxWidth, mMaxHeight, mPalette );
	info.SetValues( swidth, sheight, mSymbols.size(), &box );
	mSymbols.push_back( info );
}



void FontInfo::ClearPalette()
{
	if (mPalette != NULL)
		delete mPalette;
}



bool FontInfo::SetPalette(Palette* pal)
{
	wxASSERT( pal );
	ClearPalette();
	mPalette = pal->Clone();
	if ( mPalette->IsOk() )
	{
		ChangePaletteEvent palEvent( wxID_FONTEDITOR, pal );
		wxTheApp->QueueEvent( palEvent.Clone() );
	}
	return mPalette->IsOk();
}