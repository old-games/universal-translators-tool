/***************************************************************
 * Name:      symbolinfo.cpp
 * Purpose:   SymbolInfo used to store a single font symbol
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-07-02
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "symbolinfo.h"

void SymbolInfo::SetValues(int width, int height, unsigned int code, LetterBox* data /* NULL */)
{
	mWidth = width;
	mHeight = height;
	mCode = code;
	if (data != NULL)
	{
		SetData( data );
	}
	else
	{
		EraseData();
	}
}



/* virtual */ SymbolInfo::~SymbolInfo()
{
	EraseData();
}



inline SymbolInfo &SymbolInfo::operator = ( const SymbolInfo &src )
{
	this->SetValues(src.mWidth, src.mHeight, src.mCode, src.mData);
	return *this;
}

void SymbolInfo::SetData(const LetterBox* data /* NULL */)
{
	CreateData();
	if (data)
	{
		memcpy(mData, data, sizeof( LetterBox ));
	}
}

inline void SymbolInfo::CreateData()
{
	EraseData();
	if (mData == NULL)
	{
		mData = (LetterBox*) malloc(sizeof(LetterBox));
		memset( mData, 0, sizeof(LetterBox) );
	}
}

inline void SymbolInfo::EraseData()
{
	if (mData != NULL)
	{
		free(mData);
		mData = NULL;
	}
}

LetterBox* SymbolInfo::GetData()
{
	wxASSERT( mData != NULL );
	return mData;
}

inline int SymbolInfo::BoxOffset(int x, int y)
{
	wxInt32 offset = (x * MAXIMUM_SYMBOL_WIDTH) + y;
	if ( (size_t) offset >= sizeof(LetterBox) )
	{
		wxLogMessage( wxString::Format("SymbolInfo::BoxOffset: coordinates are out of range (X: %d, Y: %d)", x, y) );
		return -1;
	}
	return offset;
}

void SymbolInfo::SetPixel( int x, int y, RGBA color )
{
	int offset = BoxOffset(x, y);
	if ( offset < 0 )
	{
		return;
	}
	Pixel& val = *mData[offset];
	val[0] = color.R;
	val[1] = color.G;
	val[2] = color.B;
}

RGBA SymbolInfo::GetPixel( int x, int y )
{
	RGBA res;
	int offset = BoxOffset(x, y);
	if ( offset < 0 )
	{
		return res;
	}
	Pixel& val = *mData[offset];
	res.R = val[0];
	res.G = val[1];
	res.B = val[2];
	return res;
}

