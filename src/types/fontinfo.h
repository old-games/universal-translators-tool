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

class Palette;

class FontInfo
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

	bool SetPalette(Palette* pal);

	static SymbolInfo	sBadSymbol;

private: 
	void ClearPalette();

	wxInt32			mMaxHeight;							// ������������ ������
	wxInt32			mMinHeight;							// ����������� ������
	wxInt32			mMaxWidth;							// ������������ ������
	wxInt32			mMinWidth;							// ����������� ������
	wxInt32			mBaseLine;							// ������� ����� �������
	wxInt32			mCapLine;							// ����� ��������� ����
	wxInt32			mLowLine;							// ����� �������� ����
	wxInt32			mBPP;								// ��� �� �������
	wxInt32			mFontCodePage;						// ���������, ������������� ��������, ��� ������� ������������� ������
	Symbols			mSymbols;							// �������
	Palette*        mPalette;							// �������


};



#endif // FONTINFO_H_INCLUDED