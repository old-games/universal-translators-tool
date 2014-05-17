/***************************************************************
 * Name:      buffer.cpp
 * Purpose:   implementation of Buffer class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "buffer.h"



Buffer::Buffer():
	mData(NULL),
	mSize(0),
	mOwnData( false )
{
}



Buffer::Buffer( const std::string& src ):
	mData(NULL),
	mSize(0),
	mOwnData( false )
{
	SetData( src );
}



Buffer::Buffer( void* src, size_t size, bool ownData /* true */):
	mData(NULL),
	mSize(0),
	mOwnData( false )
{
	SetData( src, size, ownData );
}


Buffer::Buffer( const Buffer& other ):
	mData(NULL),
	mSize( 0 ),
	mOwnData( false )
{
	SetData( other.mData, mSize, false );
}



Buffer::~Buffer()
{
	Clear();
}



void Buffer::Clear()
{
	if ( mData )
	{
		free(mData);
		mData = NULL;
	}
}



void Buffer::SetData( void* src, size_t size, bool ownData /* true */ )
{
	Clear();
	
	if (ownData)
	{
		mData = src;
	}
	else
	{
		mData = malloc(size);
		memcpy(mData, src, size);
	}

	mSize = size;
	mOwnData = ownData;
}



void Buffer::SetData( const std::string& src )
{
	SetData( (void*) src.c_str(), src.length(), false );
}



std::string Buffer::GetBufferAsString()
{
	if (!IsOk())
	{
		return std::string();
	}
	return std::string((char*) mData, mSize);
}
