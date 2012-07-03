/***************************************************************
 * Name:      fontinfo.h
 * Purpose:   declaration of FontInfo class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-07-02
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef FONTINFO_H_INCLUDED
#define FONTINFO_H_INCLUDED

#include "symbolinfo.h"



class FontInfo
{

public:

	FontInfo():
		mMaxHeight( 0 ),
		mMinHeight( 0 ),
		mMaxWidth( 0 ),
		mMinWidth( 0 ),
		mBaseLine( 0 ),
		mCapLine( 0 ),
		mLowLine( 0 ),
		mBPP( BPP::bppMono ),
		mFontCodePage( 0 )
	{
		SetSymbolsNum( MINIMUM_SYMBOLS_NUM );
		memset(mPalette, 0, sizeof(mPalette));
	}

	void SetValues( int maxWidth, int maxHeight, int minWidth, int minHeight,
					int bpp = BPP::bppMono,
					int fontCodePage = wxFONTENCODING_DEFAULT,
					int baseLine = 0,
					int capLine = 0,
					int lowLine = 0 );

	wxInt32 GetEncoding()
	{
		return mFontCodePage;
	}

	void SetEncoding(wxInt32 n)
	{
		mFontCodePage = n;
	}


	size_t GetSymbolsNum();
	void SetSymbolsNum(size_t n);



	SymbolInfo& GetSymbol(size_t n);


	Symbols& GetSymbols()
	{
		return mSymbols;
	}

	void SetSymbols(const Symbols& src)
	{
		mSymbols = src;
	}

	void AddSymbol( const char* data, int width, int height );

	wxInt32 GetMaxWidth()
	{
		return mMaxWidth;
	}

	void SetMaxWidth( wxInt32 width )
	{
		mMaxWidth = width;
	}

	wxInt32 GetMaxHeight()
	{
		return mMaxHeight;
	}

	void SetMaxHeight( wxInt32 height )
	{
		mMaxHeight = height;
	}

	wxInt32 GetMinWidth()
	{
		return mMinWidth;
	}

	void SetMinWidth( wxInt32 width )
	{
		mMinWidth = width;
	}

	wxInt32 GetMinHeight()
	{
		return mMinHeight;
	}

	void SetMinHeight( wxInt32 height )
	{
		mMinHeight = height;
	}

	wxInt32	GetBaseLine()
	{
		return mBaseLine;
	}

	void SetBaseLine(wxInt32 baseLine)
	{
		mBaseLine = baseLine;
	}

	wxInt32	GetCapLine()
	{
		return mCapLine;
	}

	void SetCapLine(wxInt32 capLine)
	{
		mCapLine = capLine;
	}

	wxInt32	GetLowLine()
	{
		return mLowLine;
	}

	void SetLowLine(wxInt32 lowLine)
	{
		mLowLine = lowLine;
	}

	static SymbolInfo	sBadSymbol;

protected:

	wxInt32			mMaxHeight;							// максимальная высота
	wxInt32			mMinHeight;							// минимальная высота
	wxInt32			mMaxWidth;							// максимальная ширина
	wxInt32			mMinWidth;							// минимальная ширина
	wxInt32			mBaseLine;							// базовая линия символа
	wxInt32			mCapLine;							// линия заглавных букв
	wxInt32			mLowLine;							// линия строчных букв
	wxInt32			mBPP;								// бит на пиксель
	wxInt32			mFontCodePage;						// кодировка, относительный параметр, для лучшего представления шрифта
	Palette         mPalette;							// палитра
	Symbols			mSymbols;							// символы

};



#endif // FONTINFO_H_INCLUDED
