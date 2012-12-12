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



Origin::Origin( OriginEnum origin ):
	IStateStore( ORIGINNAME, ORIGINVERSION ),
	mOriginFrom(origin),
	mOriginFileName( wxEmptyString ),
	mOriginAdditional( wxEmptyString )
{
}


	
Origin::Origin( const Origin& other ):
	IStateStore( ORIGINNAME, ORIGINVERSION ),
	mOriginFrom( other.mOriginFrom ),
	mOriginFileName( other.mOriginFileName ),
	mOriginAdditional( other.mOriginAdditional )
{
}



void Origin::SetOriginFileName( const wxString& fileName )
{
	mOriginFileName = fileName;
}



void Origin::SetOriginAdditional( const wxString& additional )
{
	mOriginAdditional = additional;
}



/* virtual */ bool Origin::SaveState( wxOutputStream& output )
{
	bool res = SaveSimpleType<wxInt32>( output, mOriginFrom) &&
		SaveString( output, mOriginFileName ) &&
		SaveString( output, mOriginAdditional );

	return res;
}



/* virtual */ bool Origin::LoadState( wxInputStream& input, int version )
{
	version;	// unused yet, must exist
	
	
	bool res = LoadSimpleType<wxInt32>( input, (wxInt32&) mOriginFrom) &&
		LoadString( input, mOriginFileName ) &&
		LoadString( input, mOriginAdditional );
	return res;
}
