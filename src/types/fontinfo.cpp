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
#include "indexmask.h"



const wxString	FINFONAME = "FontInfo";
const int		FINFOVERSION = 0x100;



FontInfo::FontInfo():
	IInfo( FINFONAME, FINFOVERSION, etFont ),
	mMaxHeight( 0 ),
	mMinHeight( 0 ),
	mMaxWidth( 0 ),
	mMinWidth( 0 ),
	mBaseLine( 0 ),
	mCapLine( 0 ),
	mLowLine( 0 ),
	mBPP( Palette::bppMono ),
	mFontCodePage( 0 ),
	mPalette()
{
}



FontInfo::FontInfo( const FontInfo& other ):
	IInfo( other ),
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
	mPalette()
{
	if (other.mPalette)
	{
		mPalette = other.mPalette->Clone();
	}
}



FontInfo::~FontInfo()
{
	mSymbols.clear();
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



size_t FontInfo::GetSymbolsNum() const
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



SymbolInfoPtr FontInfo::GetSymbol(size_t n) const
{
	return n < mSymbols.size() ? mSymbols[n] : nullptr;
}



void FontInfo::AddSymbolFromBuf( const wxByte* data, int width, int height, int swidth, int sheight )
{
	wxASSERT( mPalette != NULL );
	IndexMaskPtr mask = std::make_shared<IndexMask>();
	mask->SetMask( data, width * height, width, height );

	if (mask->IsOk())
	{
		AddSymbolIndexed(mask, swidth, sheight);
	}
}



void FontInfo::AddSymbolIndexed( IndexMaskPtr mask, int swidth, int sheight )
{
	wxASSERT( mPalette != NULL );
	SymbolInfoPtr info = std::make_shared<SymbolInfo>();
	info->SetValues(swidth, sheight, mSymbols.size(), mask);
	mSymbols.push_back(info);
}



bool FontInfo::SetPalette(PalettePtr pal)
{
	wxASSERT( pal );
	mPalette = pal;//->Clone();
	return mPalette->IsOk();
}



/* virtual */ bool FontInfo::SaveState( wxOutputStream& output )
{
	if (!mPalette || !mPalette->IsOk())
	{
		wxLogError("FontInfo::SaveState: can't save font without palette!");
		return false;
	}

	bool res = IInfo::SaveState( output ) &&
		SaveSimpleType<wxInt32>( output, mMaxHeight ) &&
		SaveSimpleType<wxInt32>( output, mMinHeight ) &&
		SaveSimpleType<wxInt32>( output, mMaxWidth ) &&
		SaveSimpleType<wxInt32>( output, mMinWidth ) &&
		SaveSimpleType<wxInt32>( output, mBaseLine ) &&
		SaveSimpleType<wxInt32>( output, mCapLine ) &&
		SaveSimpleType<wxInt32>( output, mLowLine ) &&
		SaveSimpleType<wxInt32>( output, mBPP ) &&
		SaveSimpleType<wxInt32>( output, mFontCodePage ) &&
		SaveSimpleType<wxUint32>( output, mSymbols.size() );

	if (res)
	{
		for (size_t i = 0; i < mSymbols.size() && res; ++i)
		{
			res = mSymbols[i]->SaveToStream(output);
		}

		if (res)
		{
			res = mPalette->SaveToStream(output);
		}
	}

	return res;
}



/* virtual */ bool FontInfo::LoadState( wxInputStream& input, int version )
{
	version;	// unused yet, must exist
	
	wxUint32 symNum = 0;
	mPalette = nullptr;
	mSymbols.clear();

	bool res = IInfo::LoadState( input, version ) &&
		LoadSimpleType<wxInt32>( input, mMaxHeight ) &&
		LoadSimpleType<wxInt32>( input, mMinHeight ) &&
		LoadSimpleType<wxInt32>( input, mMaxWidth ) &&
		LoadSimpleType<wxInt32>( input, mMinWidth ) &&
		LoadSimpleType<wxInt32>( input, mBaseLine ) &&
		LoadSimpleType<wxInt32>( input, mCapLine ) &&
		LoadSimpleType<wxInt32>( input, mLowLine ) &&
		LoadSimpleType<wxInt32>( input, mBPP ) &&
		LoadSimpleType<wxInt32>( input, mFontCodePage ) &&
		LoadSimpleType<wxUint32>( input, symNum );

	if (res)
	{
		for (size_t i = 0; i <  symNum && res; ++i)
		{
			SymbolInfoPtr info = std::make_shared<SymbolInfo>();
			res = info->LoadFromStream( input );

			if (res)
			{
				mSymbols.push_back( info );
			}
		}

		if (res)
		{
			PalettePtr pal = std::make_shared<Palette>();

			if (pal->LoadFromStream(input))
			{
				res = SetPalette( pal );
			}
		}
	}

	return res;
}


