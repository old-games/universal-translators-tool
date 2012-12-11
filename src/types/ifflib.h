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


struct IFFChunkInfo: public LibItemData
{
	IFFChunkInfo( IFFChunk& chunk ):
		mChunkName(wxEmptyString),
		mFormDescription(wxEmptyString),
		mOffset(wxInvalidOffset),
		mDataOffset(wxInvalidOffset),
		mChunkSize(wxInvalidOffset)
	{
		mChunkName = wxString( chunk.CHUNKID, sizeof(chunk.CHUNKID) );
		mChunkSize = chunk.SIZE;
	}

	IFFChunkInfo( const IFFChunkInfo& other );

	IFFChunkInfo* Clone() { return new IFFChunkInfo(*this); }

	bool InitFromStream(wxInputStream* input);
	inline bool IsFORM() { return !mFormDescription.IsEmpty(); }

	wxString		mChunkName;
	wxString		mFormDescription;
	wxFileOffset	mOffset;
	wxFileOffset	mDataOffset;
	wxFileOffset	mChunkSize;
	
};


class IFFLib: public LibTree
{
public:
	IFFLib(bool bigEndian = true);
	virtual ~IFFLib();

	bool LoadIFFFile( const char* fileName );			// overload for Lua
	bool LoadIFFFile( const wxString& fileName );
	bool LoadIFFStream( wxInputStream& input, LibItem* parent );

	LibItem* FindForm( const char* formDesc );
	LibItem* FindSubForm( const char* formDesc, LibItem* startItem );
	LibItem* FindChunk( const char* chunkName, LibItem* formItem );

	char* ReadChunkData( LibItem* item );
	
protected:

	bool ReadChunk( wxInputStream& input, IFFChunk& chunk );

private:

	bool		mBigEndian;
	wxString	mIFFFile;
};

#endif // IFFLIB_H_INCLUDED
