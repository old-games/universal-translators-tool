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
#include "indexmask.h"

void SymbolInfo::SetValues(int width, int height, unsigned int code, IndexMask* data /* NULL */)
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



void SymbolInfo::SetData(const IndexMask* data /* NULL */)
{
	EraseData();
	mData = data->Clone();
}


//
//inline void SymbolInfo::CreateData()
//{
//	EraseData();
//	if (mData == NULL)
//	{
//		mData = new IndexMask();
//	}
//}



inline void SymbolInfo::EraseData()
{
	if (mData != NULL)
	{
		delete mData;
		mData = NULL;
	}
}



IndexMask* SymbolInfo::GetData()
{
	wxASSERT( mData != NULL );
	return mData;
}




//inline int SymbolInfo::BoxOffset(int x, int y)
//{
//	wxInt32 offset = (x * MAXIMUM_SYMBOL_WIDTH) + y;
//	if ( (size_t) offset >= sizeof(LetterBox) )
//	{
//		wxLogMessage( wxString::Format("SymbolInfo::BoxOffset: coordinates are out of range (X: %d, Y: %d)", x, y) );
//		return -1;
//	}
//	return offset;
//}



void SymbolInfo::SetWidth( int w )
{
	mWidth = w;
}



void SymbolInfo::SetHeight( int h )
{
	mHeight = h;
}

