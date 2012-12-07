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


bool IFFChunkInfo::InitFromStream(wxInputStream* input)
{
	bool success = false;

	if (input != 0)
	{
		mOffset = input->SeekI(0, wxFromCurrent) - sizeof(IFFChunk);

		if (mChunkName == "FORM")
		{
			wxByte desc[4];
			input->Read(&desc, sizeof(desc));
			
			if (input->LastRead() == sizeof(desc))
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



bool IFFLib::LoadIFFFile( const wxString& fileName )
{
	wxFileInputStream stream(fileName);
	bool res = false;

	if ( stream.IsOk() )
	{
		wxBusyInfo info("Loading, please wait...");
		res = LoadIFFStream( stream );
	}
	else
	{
		wxLogError(wxString::Format("IFFLib::LoadIFFFile: can't open file (%s)!",  fileName));
	}

	return res;
}



bool IFFLib::LoadIFFStream( wxInputStream& input )
{
	IFFChunk chunk;
	bool success = ReadChunk( input, chunk );
	
	if (success)
	{
		IFFChunkInfo info(chunk);
		success = info.InitFromStream(&input);
		
		if (success)
		{
			if (!info.IsFORM())
			{
				input.SeekI( info.mChunkSize, wxFromCurrent );
			}

			LoadIFFStream( input );
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