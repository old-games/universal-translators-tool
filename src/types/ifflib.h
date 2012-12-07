/***************************************************************
 * Name:      ifflib.h
 * Purpose:   declaration of IFFLib class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-07
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef IFFLIB_H_INCLUDED
#define IFFLIB_H_INCLUDED


#include "libtree.h"


struct IFFChunk
{
	wxByte		CHUNKID[4];
	wxUint32	SIZE;
};


struct IFFChunkInfo
{
	IFFChunkInfo( IFFChunk& chunk )
	{
		mChunkName = wxString( chunk.CHUNKID, sizeof(chunk.CHUNKID) );
		mChunkSize = chunk.SIZE;
	}

	bool InitFromStream(wxInputStream* input);
	inline bool IsFORM() { return !mFormDescription.IsEmpty(); }

	wxString		mChunkName;
	wxString		mFormDescription;
	wxFileOffset	mOffset;
	wxFileOffset	mChunkSize;
	
};


class IFFLib: public LibTree
{
public:
	IFFLib(bool bigEndian = true);
	virtual ~IFFLib();

	bool LoadIFFFile( const wxString& fileName );
	bool LoadIFFStream( wxInputStream& input );

protected:

	bool ReadChunk( wxInputStream& input, IFFChunk& chunk );

private:

	bool	mBigEndian;
};

#endif // IFFLIB_H_INCLUDED
