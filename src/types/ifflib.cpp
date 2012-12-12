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
#include "luacontrol.h"
#include "buffer.h"

IFFChunkInfo::IFFChunkInfo( const IFFChunkInfo& other ):
	LibItemData( other ),
	mChunkName( other.mChunkName ),
	mFormDescription( other.mFormDescription ),
	mOffset( other.mOffset ),
	mDataOffset(other.mDataOffset ),
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

		mDataOffset = input->SeekI(0, wxFromCurrent);
	}

	return success;
}



//////////////////////////////////////////////////////////////////////////



IFFLib::IFFLib(bool bigEndian /* true */): LibTree(),
	mBigEndian( bigEndian ),
	mIFFFile( wxEmptyString )
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

		if (res)
		{
			mIFFFile = fileName;
		}
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



LibItem* IFFLib::FindForm( const char* formDesc )
{
	return FindSubForm( formDesc, GetRoot() );
}



LibItem* IFFLib::FindSubForm( const char* formDesc, LibItem* startItem )
{

	IFFChunkInfo* data = static_cast<IFFChunkInfo*>(startItem->GetData());
	if (data && data->IsFORM() && data->mFormDescription == formDesc)
	{
		return startItem;
	}

	for (ItemsArrayIterator it = startItem->GetChildrenBegin();
			it != startItem->GetChildrenEnd(); ++it)
	{
		LibItem* result = FindSubForm(formDesc, *it);

		if (result)
		{
			return result;
		}
	}

	return &LibItem::BAD_ITEM;
}



LibItem* IFFLib::FindChunk( const char* chunkName, LibItem* formItem )
{
	for (ItemsArrayIterator it = formItem->GetChildrenBegin();
			it != formItem->GetChildrenEnd(); ++it)
	{
		IFFChunkInfo* data = static_cast<IFFChunkInfo*>( (*it)->GetData() );

		if (data && data->mChunkName == chunkName)
		{
			return *it;
		}
	}

	return &LibItem::BAD_ITEM;
}



void* IFFLib::ReadChunkData( LibItem* item, size_t& size )
{
	wxASSERT( item );

	IFFChunkInfo* data = static_cast<IFFChunkInfo*>( item->GetData() );
	wxFileInputStream stream(mIFFFile);
	void* res = NULL;
	size = 0;
	if ( stream.IsOk() && data )
	{
		size = data->mChunkSize;
		res = malloc(size);
		stream.SeekI( data->mDataOffset );
		stream.Read( res, size );
	}

	return res;
}



std::string IFFLib::ReadChunkData( LibItem* item )
{
	size_t size = 0;
	void* buf = ReadChunkData(item, size);

	if (!buf)
	{
		return std::string();
	}

	std::string res( (char*) buf, size);
	free(buf);

	return res;
}