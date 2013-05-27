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



Origin::Origin( const char* fileName ):
	IStateStore( ORIGINNAME, ORIGINVERSION ),
	mOriginFrom(FromFile),
	mOriginFileName( fileName ),
	mOriginAdditional( wxEmptyString ),
	mOffset(0),
	mSize(0),
	mParent(NULL)
{
	mSize = wxFileName::GetSize(fileName);
}



Origin::Origin( Origin* parent, wxFileOffset offset, wxFileOffset size ):
	IStateStore( ORIGINNAME, ORIGINVERSION ),
	mOriginFrom(FromLibrary),
	mOriginFileName( wxEmptyString ),
	mOriginAdditional( wxEmptyString ),
	mOffset(offset),
	mSize(size),
	mParent(NULL)
{
	SetParent(parent);
}

Origin::Origin( const Origin& other ):
	IStateStore( ORIGINNAME, ORIGINVERSION ),
	mOriginFrom( other.mOriginFrom ),
	mOriginFileName( other.mOriginFileName ),
	mOriginAdditional( other.mOriginAdditional ),
	mParent(NULL)
{
	SetParent(other.GetParent());
}



/* virtual */ Origin::~Origin()
{
	delete mParent;
}



void Origin::SetParent(const Origin* parent)
{
	delete mParent;
	mParent = NULL;
	
	if (parent)
	{
		mParent = parent->Clone();
	}
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



const Origin* Origin::GetParent() const
{
	return mParent;
}



/* virtual */ bool Origin::SaveState( wxOutputStream& output )
{
	bool hasParent = mParent && mParent->GetOrigin() != Unknown;
	bool res = SaveSimpleType<wxInt32>( output, mOriginFrom) &&
		SaveString( output, mOriginFileName ) &&
		SaveString( output, mOriginAdditional ) && 
		SaveSimpleType<wxFileOffset>( output, mOffset) &&
		SaveSimpleType<wxULongLong>( output, mSize) &&
		SaveSimpleType<bool>(output, hasParent);
	
	if (hasParent)
	{
		res = mParent->SaveState(output);
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
		if (!mParent)
		{
			mParent = new Origin();
		}
		res = mParent->LoadState(input, version);
	}

	return res;
}
