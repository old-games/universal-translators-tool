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
	mData()
{}



SymbolInfo::SymbolInfo( const SymbolInfo& other ):
	IStateStore( SYMINFONAME, SYMINFOVERSION ),
	mWidth( other.mWidth ),
	mHeight( other.mHeight ),
	mCode( other.mCode ),
	mData( other.mData ? other.mData->Clone() : other.mData)
{
}



void SymbolInfo::SetValues(int width, int height, unsigned int code,
	IndexMaskPtr data /* nullptr */)
{
	mWidth = width;
	mHeight = height;
	mCode = code;
	mData = data;
}



/* virtual */ SymbolInfo::~SymbolInfo()
{
}



//inline SymbolInfo &SymbolInfo::operator = ( const SymbolInfo &src )
//{
//	this->SetValues(src.mWidth, src.mHeight, src.mCode, src.mData);
//	return *this;
//}



void SymbolInfo::SetData(IndexMaskPtr data)
{
	mData = data;
}




IndexMaskPtr SymbolInfo::GetData()
{
	wxASSERT( mData != nullptr);
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
	mData = std::make_shared<IndexMask>();

	bool res = LoadSimpleType<wxInt32>( input, mWidth ) &&
		LoadSimpleType<wxInt32>( input, mHeight ) &&
		LoadSimpleType<wxUint32>( input, mCode ) &&
		mData->LoadFromStream( input );

	return res && this->IsOk();
}
