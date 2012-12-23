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

const wxString	IMINFONAME = "ImageInfo";
const int		IMINFOVERSION = 0x100;


ImageInfo::ImageInfo(): 
	IInfo( IMINFONAME, IMINFOVERSION, etImage ),
	mIndexMask(NULL),
	mPalette(NULL)
{
}



ImageInfo::ImageInfo(IndexMask* mask, Palette* pal):
	IInfo( IMINFONAME, IMINFOVERSION, etImage ),
	mIndexMask(NULL),
	mPalette(NULL)
{
	SetImage( mask );
	SetPalette( pal );
}



ImageInfo::ImageInfo( const ImageInfo& other ):
	IInfo( other ),
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
	
	wxRect checkRect = rect;
	checkRect.Intersect( wxRect(0, 0, mIndexMask->GetWidth(), mIndexMask->GetHeight()) );
	if ( !(checkRect.GetWidth() >= 0 && checkRect.GetHeight() >= 0) )
	{
		return NULL;
	}
	int w = checkRect.GetWidth();
	int h = checkRect.GetHeight();

	size_t size = mPalette->GetCorrectImageSize(w, h, true);
	wxByte* buf = (wxByte*) malloc( size );
	int bytesOnPixel = size / (w * h);

	switch (bytesOnPixel)
	{
		case 1:
			Helpers::CropSubBuffer( buf, w, h, mIndexMask->GetMask(), 
								mIndexMask->GetWidth(), rect.x, rect.y);
		break;

		case 2:
			Helpers::CropSubBuffer<short>((short*) buf, w, h, (const short*) mIndexMask->GetMask(), 
								mIndexMask->GetWidth(), rect.x, rect.y);
		break;

		case 3:
			Helpers::CropSubBuffer<Pixel>((Pixel*)(buf), w, h, 
								(const Pixel*) mIndexMask->GetMask(), 
								mIndexMask->GetWidth(), rect.x, rect.y);
		break;

		case 4:
			Helpers::CropSubBuffer<PixelA>((PixelA*) buf, w, h, (const PixelA*) mIndexMask->GetMask(), 
								mIndexMask->GetWidth(), rect.x, rect.y);
		break;

		default:
			wxLogError( wxString::Format("ImageInfo::CopyToImageInfo: Bytes on pixel = %d", bytesOnPixel));
	}

	
	
	IndexMask mask;
	mask.SetMask( buf, size, w, h );
	
	free(buf);
 
	ImageInfo* info = new ImageInfo( &mask, mPalette);
	if (!info->IsOk())
	{
		delete info;
		info = NULL;
	}
	return info;
}



bool ImageInfo::PasteImageInfo( const wxPoint& point, const ImageInfo* src )
{
	bool res = false;
	size_t size = mPalette->GetCorrectImageSize(10, 10, true);
	int bytesOnPixel = size / (10 * 10);

	switch (bytesOnPixel)
	{
		case 1:
			res = mIndexMask->InsertMask<char>( point, src->GetImage() );
		break;

		case 2:
			res = mIndexMask->InsertMask<short>( point, src->GetImage() );
		break;

		case 3:
			res = mIndexMask->InsertMask<Pixel>( point, src->GetImage() );
		break;

		case 4:
			res = mIndexMask->InsertMask<PixelA>( point, src->GetImage() );
		break;

		default:
			wxLogError( wxString::Format("ImageInfo::PasteImageInfo: Bytes on pixel = %d", bytesOnPixel));
	}
	return res;
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




/* virtual */ bool ImageInfo::SaveState( wxOutputStream& output )
{
	if (!IsOk())
	{
		wxLogError("ImageInfo::SaveState: can't save bad image info!");
		return false;
	}

	bool res = IInfo::SaveState( output ) &&
		mIndexMask->SaveToStream(output) && mPalette->SaveToStream(output);

	return res;
}



/* virtual */ bool ImageInfo::LoadState( wxInputStream& input, int version )
{
	version;	// unused yet, must exist
	
	Clear();
	mIndexMask = new IndexMask();
	mPalette = new Palette();

	bool res = IInfo::LoadState( input, version ) &&
		mIndexMask->LoadFromStream(input) && mPalette->LoadFromStream(input);

	if (!res)
	{
		Clear();
	}

	return res;
}
