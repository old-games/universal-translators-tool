/***************************************************************
 * Name:      ifflib.cpp
 * Purpose:   implementation of IFFLib class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-07
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "ifflib.h"



IFFChunkInfo::IFFChunkInfo( const IFFChunkInfo& other ):
	LibItemData( other ),
	mChunkName( other.mChunkName ),
	mFormDescription( other.mFormDescription ),
	mOffset( other.mOffset ),
	mChunkSize( other.mChunkSize )
{
}



bool IFFChunkInfo::InitFromStream(wxInputStream* input)
{
	bool success = false;

	if (input != NULL)
	{
		mOffset = input->SeekI(0, wxFromCurrent) - sizeof(IFFChunk);
		success = mOffset != wxInvalidOffset;

		if (mChunkName == "FORM")
		{
			wxByte desc[4];
			input->Read(&desc, sizeof(desc));
			success = input->LastRead() == sizeof(desc);

			if ( success )
			{
				mFormDescription = wxString(desc, sizeof(desc));
			}
		}
	}

	return success;
}



//////////////////////////////////////////////////////////////////////////



IFFLib::IFFLib(bool bigEndian /* true */): LibTree(),
	mBigEndian( bigEndian )
{
}



/* virtual */ IFFLib::~IFFLib()
{
}



bool IFFLib::LoadIFFFile( const char* fileName )
{
	return LoadIFFFile( wxString(fileName) );
}



bool IFFLib::LoadIFFFile( const wxString& fileName )
{
	wxFileInputStream stream(fileName);
	bool res = false;

	if ( stream.IsOk() )
	{
		wxBusyInfo info("Loading, please wait...");
		res = LoadIFFStream( stream, GetRoot() );
	}
	else
	{
		wxLogError(wxString::Format("IFFLib::LoadIFFFile: can't open file (%s)!",  fileName));
	}

	return res;
}



bool IFFLib::LoadIFFStream( wxInputStream& input, LibItem* parent )
{
	wxASSERT( parent );

	IFFChunk chunk;
	bool success = ReadChunk( input, chunk );
	
	if (success)
	{
		IFFChunkInfo info(chunk);
		success = info.InitFromStream(&input);
		
		if (success)
		{
			LibItem* child = parent->AddChild();

			LibItem* nextParent = NULL;
			if ( info.IsFORM() )
			{
				child->SetText( info.mChunkName + " " + info.mFormDescription );
				nextParent = child;
			}
			else
			{
				child->SetText( info.mChunkName );
				nextParent = parent;
				input.SeekI( info.mChunkSize, wxFromCurrent );
			}

			
			child->SetData( info.Clone() );

			LoadIFFStream( input, nextParent );
		}
	}

	return success;
}



bool IFFLib::ReadChunk( wxInputStream& input, IFFChunk& chunk )
{
	input.Read( &chunk, sizeof(chunk) );
	bool success = input.LastRead() == sizeof(IFFChunk);
	
	if (mBigEndian)
	{
		Helpers::SwapEndian32( chunk.SIZE );
	}

	return success;
}