/***************************************************************
 * Name:      indexmask.cpp
 * Purpose:   Mask container for Bitmap with indexed palette
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-18
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "indexmask.h"
#include "palette.h"
#include "helpers.h"


const wxString	IMASKNAME = "IndexMask";
const int		IMASKVERSION = 0x100;


IndexMask::IndexMask(): 
	IInfo( IMASKNAME, IMASKVERSION, etImage ),
	mWidth(0), 
	mHeight(0), 
	mSize(0), 	
	mSrcWidth( 0 ),
	mSrcHeight( 0 ), 
	mMask(NULL) {}

IndexMask::IndexMask( const IndexMask& other ):
	IInfo( other ),
	mWidth( other.mWidth ),
	mHeight( other.mHeight ),
	mSize( other.mSize ),
	mSrcWidth( other.mSrcWidth ),
	mSrcHeight( other.mSrcHeight ),
	mMask( (wxByte*) malloc(other.mSize) )
{
	memcpy(mMask, other.mMask, other.mSize);
}



IndexMask::~IndexMask()
{
	Clear();
}



void IndexMask::SetMask( const char* charMask, int srcSize, int width, int height, int srcWidth /* -1 */, int srcHeight /* -1 */ )
{
	SetMask( (wxByte*) charMask, srcSize, width, height, srcWidth, srcHeight );
}



void IndexMask::SetMask( const wxByte* mask, int srcSize, int width, int height, int srcWidth /* -1 */, int srcHeight /* -1 */ )
{
	Clear();
	
	bool bmpLike = srcSize < 0;

	mWidth = width;
	mHeight = height;
	mSrcWidth = srcWidth;
	mSrcHeight = srcHeight;

	if (mSrcWidth == -1)
	{
		mSrcWidth = mWidth;
	}

	if (mSrcHeight == -1)
	{
		mSrcHeight = mHeight;
	}

	mSize = mHeight * mWidth;
	
	int bytesOnPixel = mSize / (mWidth * mHeight);

	mMask = (wxByte*) malloc( mSize );

	switch (bytesOnPixel)
	{
		case 1:
			Helpers::CopyBuffer<wxByte>( mMask, mWidth, mHeight, mask, mSrcWidth, mSrcHeight );
		break;

		case 2:
			Helpers::CopyBuffer<short>( (short*) mMask, mWidth, mHeight, (const short*)mask, mSrcWidth, mSrcHeight );
		break;

		case 3:
			Helpers::CopyBuffer<Pixel>( (Pixel*) mMask, mWidth, mHeight,  (const Pixel*) mask, mSrcWidth, mSrcHeight );
		break;

		case 4:
			Helpers::CopyBuffer<PixelA>( (PixelA*) mMask, mWidth, mHeight,  (const PixelA*) mask, mSrcWidth, mSrcHeight );
		break;

		default:
			wxLogError( wxString::Format("IndexMask::SetMask: unsupported source format! Bytes on pixel = %d", bytesOnPixel));
			Clear();
	}

	if (bmpLike)
	{
		Helpers::BufferToBMPStyle(mMask, mWidth, mHeight, bytesOnPixel);
	}
}



wxBitmap* IndexMask::GetBitmap( Palette* pal )
{
	wxBitmap* res = NULL;
	Pixel* buf = new Pixel[mSize];
	bool success = true;

	switch (pal->GetPalType())
	{
		case Palette::bppMono:
		case Palette::bpp2:
		case Palette::bpp4:
		case Palette::bpp8:
			Helpers::Buffer8bpp_to_Pixels(buf, mWidth, mHeight, mMask, mWidth, mHeight, pal);
		break;

		case Palette::bpp24:
			memcpy( buf, mMask, mSize );
		break;

		default:
			success = false;
			wxLogError("IndexMask::GetBitmap: unsupported palette type!");
	}
	
	if (success)
	{
		res = Helpers::CreateBitmap(buf, mWidth, mHeight);
	}

	delete[] buf;
	return res;
}



void IndexMask::Clear()
{
	if (mMask != NULL)
	{
		free(mMask);
		mMask = NULL;
	}
}



bool IndexMask::WriteIndex( const wxPoint& pos, int n )
{
	wxASSERT( n < 256 && pos.x < mWidth && pos.y < mHeight );
	mMask[ (pos.y * mWidth) + pos.x ] = (char) n;
	return true;
}



int IndexMask::ReadIndex( const wxPoint& pos )
{
	wxASSERT( pos.x < mWidth && pos.y < mHeight );
	return mMask[ (pos.y * mWidth) + pos.x ];
}




/* virtual */ bool IndexMask::SaveState( wxOutputStream& output )
{
	if (!IsOk())
	{
		wxLogError("IndexMask::SaveState: can't save bad indexed mask!");
		return false;
	}

	bool res = IInfo::SaveState( output ) &&
		SaveSimpleType<wxInt32>( output, mWidth ) &&
		SaveSimpleType<wxInt32>( output, mHeight ) &&
		SaveSimpleType<wxUint32>( output, mSize ) &&
		SaveSimpleType<wxInt32>( output, mSrcWidth ) &&
		SaveSimpleType<wxInt32>( output, mSrcHeight ) &&
		SaveData( output, mMask, mSize );

	return res;
}



/* virtual */ bool IndexMask::LoadState( wxInputStream& input, int version )
{
	version;	// unused yet, must exist
	
	Clear();

	bool res = IInfo::LoadState( input, version ) &&
		LoadSimpleType<wxInt32>( input, mWidth ) &&
		LoadSimpleType<wxInt32>( input, mHeight ) &&
		LoadSimpleType<wxUint32>( input, mSize ) &&
		LoadSimpleType<wxInt32>( input, mSrcWidth ) &&
		LoadSimpleType<wxInt32>( input, mSrcHeight );

	if (res)
	{
		mMask = (wxByte*) malloc( mSize );
		LoadData( input, mMask, mSize );
	}

	return res;
}
