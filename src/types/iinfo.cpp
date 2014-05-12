/***************************************************************
 * Name:      iinfo.cpp
 * Purpose:   implementation of IInfo interface
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-23
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "iinfo.h"



IInfo::IInfo( const wxString& infoName, int infoVersion, EditorType edType ):
	IStateStore( infoName, infoVersion ),
	mOrigin(),
	mEdType( edType )
{
}



IInfo::IInfo( const IInfo& other ):
	IStateStore( other ),
	mOrigin( other.mOrigin ? other.mOrigin->Clone() : other.mOrigin),
	mEdType( other.mEdType )
{
}


/* virtual */ IInfo::~IInfo()
{
}




void IInfo::SetOrigin(OriginPtr origin)
{
	mOrigin = origin;
}



OriginPtr IInfo::GetOrigin() const
{
	return mOrigin;
}



EditorType IInfo::GetEditorType() const
{
	return mEdType;
}



/* virtual */ bool IInfo::SaveState( wxOutputStream& output )
{
	bool res = mOrigin->SaveToStream( output );

	return res;
}



/* virtual */ bool IInfo::LoadState( wxInputStream& input, int version )
{
	version;	// unused yet, must exist
	
	bool res = mOrigin->LoadFromStream( input );

	return res;
}



