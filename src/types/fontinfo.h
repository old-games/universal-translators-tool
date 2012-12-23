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
#include "iinfo.h"

// forward declarations
class Palette;
class IndexMask;

class FontInfo: public IInfo
{

public:

	FontInfo();
	FontInfo( const FontInfo& other );
	~FontInfo();

	FontInfo* Clone() const { return new FontInfo(*this); } 

	void SetValues( int maxWidth, int maxHeight, int minWidth, int minHeight,
					int fontCodePage = wxFONTENCODING_DEFAULT,
					int baseLine = 0,
					int capLine = 0,
					int lowLine = 0 );

	int GetEncoding()
	{
		return mFontCodePage;
	}

	void SetEncoding(int n)
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

	void AddSymbolFromBuf( const wxByte* data, int width, int height, int swidth, int sheight );
	void AddSymbolIndexed( IndexMask* mask, int swidth, int sheight );

	int GetMaxWidth()
	{
		return mMaxWidth;
	}

	void SetMaxWidth( int width )
	{
		mMaxWidth = width;
	}

	int GetMaxHeight()
	{
		return mMaxHeight;
	}

	void SetMaxHeight( int height )
	{
		mMaxHeight = height;
	}

	int GetMinWidth()
	{
		return mMinWidth;
	}

	void SetMinWidth( int width )
	{
		mMinWidth = width;
	}

	int GetMinHeight()
	{
		return mMinHeight;
	}

	void SetMinHeight( int height )
	{
		mMinHeight = height;
	}

	int	GetBaseLine()
	{
		return mBaseLine;
	}

	void SetBaseLine(int baseLine)
	{
		mBaseLine = baseLine;
	}

	int	GetCapLine()
	{
		return mCapLine;
	}

	void SetCapLine(int capLine)
	{
		mCapLine = capLine;
	}

	int	GetLowLine()
	{
		return mLowLine;
	}

	void SetLowLine(int lowLine)
	{
		mLowLine = lowLine;
	}

	bool SetPalette(Palette* pal);
	Palette* GetPalette() { return mPalette; }

	static SymbolInfo	sBadSymbol;

protected:

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );

private: 
	void ClearPalette();

	wxInt32			mMaxHeight;							// максимальная высота
	wxInt32			mMinHeight;							// минимальная высота
	wxInt32			mMaxWidth;							// максимальная ширина
	wxInt32			mMinWidth;							// минимальная ширина
	wxInt32			mBaseLine;							// базовая линия символа
	wxInt32			mCapLine;							// линия заглавных букв
	wxInt32			mLowLine;							// линия строчных букв
	wxInt32			mBPP;								// бит на пиксель
	wxInt32			mFontCodePage;						// кодировка, относительный параметр, для лучшего представления шрифта
	Symbols			mSymbols;							// символы
	Palette*        mPalette;							// палитра
	Origin			mOrigin;


};



#endif // FONTINFO_H_INCLUDED
