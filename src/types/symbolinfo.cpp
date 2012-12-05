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



const wxString	SYMINFONAME = "SymbolInfo";
const int		SYMINFOVERSION = 0x100;



SymbolInfo::SymbolInfo(): 
	IStateStore( SYMINFONAME, SYMINFOVERSION ),
	mWidth( 0 ), 
	mHeight( 0 ), 
	mCode( 0 ), 
	mData( NULL ) 
{}



SymbolInfo::SymbolInfo( const SymbolInfo& other ):
	IStateStore( SYMINFONAME, SYMINFOVERSION ),
	mWidth( other.mWidth ),
	mHeight( other.mHeight ),
	mCode( other.mCode ),
	mData( NULL )
{
	SetData(other.mData);
}



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



void SymbolInfo::SetWidth( int w )
{
	mWidth = w;
}



void SymbolInfo::SetHeight( int h )
{
	mHeight = h;
}



bool SymbolInfo::IsOk()
{
	return mData && mData->IsOk();
}



/* virtual */ bool SymbolInfo::SaveState( wxOutputStream& output )
{
	if (!IsOk())
	{
		wxLogError("SymbolInfo::SaveState: can't save bad symbol info!");
		return false;
	}

	bool res = SaveSimpleType<wxInt32>( output, mWidth ) &&
		SaveSimpleType<wxInt32>( output, mHeight ) &&
		SaveSimpleType<wxUint32>( output, mCode ) &&
		mData->SaveToStream( output );

	return res;
}



/* virtual */ bool SymbolInfo::LoadState( wxInputStream& input, int version )
{
	version;	// unused yet, must exist
	
	EraseData();
	mData = new IndexMask();

	bool res = LoadSimpleType<wxInt32>( input, mWidth ) &&
		LoadSimpleType<wxInt32>( input, mHeight ) &&
		LoadSimpleType<wxUint32>( input, mCode ) &&
		mData->LoadFromStream( input );

	return res && this->IsOk();
}
