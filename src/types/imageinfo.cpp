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

ImageInfo*	ImageInfo::sBuffered = NULL;


ImageInfo::ImageInfo():
	mIndexMask(NULL),
	mPalette(NULL)
{
}



ImageInfo::ImageInfo(IndexMask* mask, Palette* pal):
	mIndexMask(NULL),
	mPalette(NULL)
{
	SetImage( mask );
	SetPalette( pal );
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
	Clear();
}



void ImageInfo::Clear()
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
	return mPalette->IsOk();
}



void ImageInfo::SetPaletteAsMain()
{
	if ( mPalette && mPalette->IsOk() )
	{
		ChangePaletteEvent palEvent( wxID_IMAGEEDITOR, mPalette, true );
		wxTheApp->QueueEvent( palEvent.Clone() );
	}
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



wxBitmap* ImageInfo::GetBitmap() const
{
	wxASSERT( IsOk() );
	return mIndexMask->GetBitmap( mPalette );
}



wxSize ImageInfo::GetSize() const 
{ 
	return wxSize( mIndexMask->GetWidth(), mIndexMask->GetHeight() ); 
}




bool ImageInfo::IsOk() const
{ 
	return mIndexMask && mPalette && mIndexMask->IsOk() && mPalette->IsOk(); 
}
	


ImageInfo* ImageInfo::CopyToImageInfo( const wxRect& rect )
{
	int w = rect.GetWidth();
	int h = rect.GetHeight();

	size_t size = w * h;
	char* buf = (char*) malloc( size );
	
	Helpers::CropSubBuffer( buf, w, h, mIndexMask->GetMask(), 
		mIndexMask->GetWidth(), rect.x, rect.y);
	
	IndexMask mask;
	mask.SetMask( buf, w, h );
	
	free(buf);
 
	ImageInfo* info = new ImageInfo( &mask, mPalette);
	if (!info->IsOk())
	{
		delete info;
		info = NULL;
	}
	return info;
}



bool ImageInfo::CopyToClipBoard( const wxRect& rect )
{
	bool res = false;
	ImageInfo* newBuffered = CopyToImageInfo( rect );
	if (newBuffered->IsOk())
	{
	
		delete sBuffered;
		sBuffered = newBuffered;
		
		wxBitmap* bmp = sBuffered->GetBitmap();
		Helpers::CopyToClipboard(bmp->ConvertToImage());
		delete bmp;

		res = true;
	}
	else
	{
		delete newBuffered;
	}
	return res;
}



//////////////////////////////////////////////////////////////////////////



ImageInfoDataObject::ImageInfoDataObject( const ImageInfo* info ):
	wxBitmapDataObject( *info->GetBitmap() ),
	mImageInfo( info->Clone() )
{

}



ImageInfoDataObject::ImageInfoDataObject( const ImageInfoDataObject& other ):
	wxBitmapDataObject( *other.mImageInfo->GetBitmap() ),
	mImageInfo( other.mImageInfo->Clone() )
{

}



ImageInfoDataObject::~ImageInfoDataObject()
{
	delete mImageInfo;
}



ImageInfo* ImageInfoDataObject::GetInfo()
{
	return mImageInfo;
}

