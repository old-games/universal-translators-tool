/***************************************************************
 * Name:      origin.cpp
 * Purpose:   implementation of Origin class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "origin.h"


const wxString	ORIGINNAME = "Origin";
const int		ORIGINVERSION = 0x100;



Origin::Origin():
	IStateStore( ORIGINNAME, ORIGINVERSION ),
	mOriginFrom(Unknown),
	mOriginFileName( wxEmptyString ),
	mOriginAdditional( wxEmptyString ),
	mOffset(wxInvalidOffset),
	mSize(wxInvalidOffset),
	mParent()
{
}



Origin::Origin( const std::string& fileName ):
	IStateStore( ORIGINNAME, ORIGINVERSION ),
	mOriginFrom(FromFile),
	mOriginFileName( fileName.c_str() ),
	mOriginAdditional( wxEmptyString ),
	mOffset(0),
	mSize(0),
	mParent()
{
	mSize = wxFileName::GetSize(mOriginFileName);
}



Origin::Origin( OriginPtr parent, wxFileOffset offset, wxFileOffset size ):
	IStateStore( ORIGINNAME, ORIGINVERSION ),
	mOriginFrom(FromLibrary),
	mOriginFileName( wxEmptyString ),
	mOriginAdditional( wxEmptyString ),
	mOffset(offset),
	mSize(size),
	mParent()
{
	SetParent(parent);
}

Origin::Origin( const Origin& other ):
	IStateStore( ORIGINNAME, ORIGINVERSION ),
	mOriginFrom( other.mOriginFrom ),
	mOriginFileName( other.mOriginFileName ),
	mOriginAdditional( other.mOriginAdditional ),
	mParent()
{
	SetParent(other.GetParent());
}



/* virtual */ Origin::~Origin()
{
}



void Origin::SetParent(OriginPtr parent)
{
	mParent = parent;
	//
	//if (parent)
	//{
	//	mParent = parent->Clone();
	//}
}



void Origin::SetOriginFileName( const wxString& fileName )
{
	mOriginFileName = fileName;
}



void Origin::SetOriginAdditional( const wxString& additional )
{
	mOriginAdditional = additional;
}



const wxString& Origin::GetFullPath() const
{
	return mOriginFileName;
}



wxString Origin::GetPath() const
{
	wxString path, name, ext;
	wxFileName::SplitPath( mOriginFileName, &path, &name, &ext );
	return path;
}



wxString Origin::GetFileName() const
{
	wxString path, name, ext;
	wxFileName::SplitPath( mOriginFileName, &path, &name, &ext );
	return name + "." + ext;
}



OriginPtr Origin::GetParent() const
{
	return mParent.lock();
}



/* virtual */ bool Origin::SaveState( wxOutputStream& output )
{
	auto parent = mParent.lock();
	bool hasParent = parent && parent->GetOrigin() != Unknown;
	bool res = SaveSimpleType<wxInt32>( output, mOriginFrom) &&
		SaveString( output, mOriginFileName ) &&
		SaveString( output, mOriginAdditional ) && 
		SaveSimpleType<wxFileOffset>( output, mOffset) &&
		SaveSimpleType<wxULongLong>( output, mSize) &&
		SaveSimpleType<bool>(output, hasParent);
	
	if (hasParent)
	{
		res = parent->SaveState(output);
	}

	return res;
}



/* virtual */ bool Origin::LoadState( wxInputStream& input, int version )
{
	version;	// unused yet, must exist
	
	bool hasParent = false;
	bool res = LoadSimpleType<wxInt32>( input, (wxInt32&) mOriginFrom) &&
		LoadString( input, mOriginFileName ) &&
		LoadString( input, mOriginAdditional ) && 
		LoadSimpleType<wxFileOffset>( input, mOffset) &&
		LoadSimpleType<wxULongLong>( input, mSize) &&
		LoadSimpleType<bool>(input, hasParent);
	
	if (hasParent)
	{
		if (!mParent.lock())
		{
			mParent = std::make_shared<Origin>();
		}

		res = mParent.lock()->LoadState(input, version);
	}

	return res;
}
