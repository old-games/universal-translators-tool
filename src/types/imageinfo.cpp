/***************************************************************
 * Name:      imageinfo.cpp
 * Purpose:   ImageInfo used to store an image
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-19
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "palette.h"
#include "imageinfo.h"
#include "indexmask.h"



ImageInfo::ImageInfo():
	mIndexMask(NULL),
	mPalette(NULL)
{
}


ImageInfo::ImageInfo( const ImageInfo& other ):
	mIndexMask( NULL ),
	mPalette( NULL )
{
	if (other.mPalette != NULL)
	{
		mPalette = other.mPalette->Clone();
	}

	if (other.mIndexMask != NULL)
	{
		mIndexMask = other.mIndexMask->Clone();
	}
}



ImageInfo::~ImageInfo()
{
	ClearPalette();
	ClearImage();
}



void ImageInfo::SetImage( IndexMask* mask )
{
	wxASSERT(mask);
	ClearImage();
	mIndexMask = mask->Clone();
}



bool ImageInfo::SetPalette(Palette* pal)
{
	wxASSERT( pal );
	ClearPalette();
	mPalette = pal->Clone();
	if ( mPalette->IsOk() )
	{
		ChangePaletteEvent palEvent( wxID_IMAGEEDITOR, mPalette, true );
		wxTheApp->QueueEvent( palEvent.Clone() );
	}
	return mPalette->IsOk();
}



void ImageInfo::ClearPalette()
{
	if (mPalette != NULL)
	{
		delete mPalette;
		mPalette = NULL;
	}
}



void ImageInfo::ClearImage()
{
	if (mIndexMask != NULL)
	{
		delete mIndexMask;
		mIndexMask = NULL;
	}
}