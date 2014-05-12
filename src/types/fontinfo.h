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



class FontInfo: public IInfo
{

public:

	FontInfo();
	FontInfo( const FontInfo& other );
	~FontInfo();

	FontInfoPtr Clone() const { return std::make_shared<FontInfo>(*this); }

	void SetValues( int maxWidth, int maxHeight, int minWidth, int minHeight,
					int fontCodePage = wxFONTENCODING_DEFAULT,
					int baseLine = 0,
					int capLine = 0,
					int lowLine = 0 );

	inline int GetEncoding() const { return mFontCodePage; }
	inline void SetEncoding(int n) { mFontCodePage = n; }

	size_t GetSymbolsNum() const;
	void SetSymbolsNum(size_t n);

	SymbolInfoPtr GetSymbol(size_t n) const;
	Symbols& GetSymbols() { return mSymbols; }

	void SetSymbols(const Symbols& src) { mSymbols = src; }

	void AddSymbolFromBuf( const wxByte* data, int width, int height, int swidth, int sheight );
	void AddSymbolIndexed( IndexMaskPtr mask, int swidth, int sheight );

	inline int GetMaxWidth() const { return mMaxWidth; }
	inline void SetMaxWidth( int width ) { mMaxWidth = width; }

	inline int GetMaxHeight() const { return mMaxHeight; }
	inline void SetMaxHeight( int height ) { mMaxHeight = height; }

	inline int GetMinWidth() const { return mMinWidth; }
	inline void SetMinWidth( int width ) { mMinWidth = width; }

	inline int GetMinHeight() const { return mMinHeight; }
	inline void SetMinHeight( int height ) { mMinHeight = height; }

	inline int	GetBaseLine() const { return mBaseLine; }
	inline void SetBaseLine(int baseLine) { mBaseLine = baseLine; }

	inline int	GetCapLine() const { return mCapLine; }
	inline void SetCapLine(int capLine) { mCapLine = capLine; }

	inline int GetLowLine() const { return mLowLine; }
	inline void SetLowLine(int lowLine) { mLowLine = lowLine; }

	bool SetPalette(PalettePtr pal);
	inline PalettePtr GetPalette() const { return mPalette; }

protected:

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );

private: 

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
	PalettePtr		mPalette;							// палитра
	Origin			mOrigin;


};



#endif // FONTINFO_H_INCLUDED
