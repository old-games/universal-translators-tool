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



ImageInfoPtr	ImageInfo::sBuffered;



const wxString	IMINFONAME = "ImageInfo";
const int		IMINFOVERSION = 0x100;



ImageInfo::ImageInfo(): 
	IInfo( IMINFONAME, IMINFOVERSION, etImage ),
	mIndexMask(),
	mPalette()
{
}



ImageInfo::ImageInfo(IndexMaskPtr mask, PalettePtr pal):
	IInfo( IMINFONAME, IMINFOVERSION, etImage ),
	mIndexMask(mask),
	mPalette(pal)
{
}



ImageInfo::ImageInfo( const ImageInfo& other ):
	IInfo( other ),
	mIndexMask(),
	mPalette()
{
	if (other.mPalette)
	{
		mPalette = other.mPalette->Clone();
	}

	if (other.mIndexMask)
	{
		mIndexMask = other.mIndexMask->Clone();
	}
}



ImageInfo::~ImageInfo()
{
}



void ImageInfo::Clear()
{
	mPalette = nullptr;
	mIndexMask = nullptr;
}



void ImageInfo::SetImage( IndexMaskPtr mask )
{
	wxASSERT(mask);
	mIndexMask = mask; //->Clone();
}



bool ImageInfo::SetPalette(PalettePtr pal)
{
	wxASSERT( pal );
	mPalette = pal; //->Clone();
	return mPalette->IsOk();
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
	


ImageInfoPtr ImageInfo::CopyToImageInfo( const wxRect& rect )
{
	ImageInfoPtr result;
	wxRect checkRect = rect;
	checkRect.Intersect( wxRect(0, 0, mIndexMask->GetWidth(), mIndexMask->GetHeight()) );

	if ( !(checkRect.GetWidth() >= 0 && checkRect.GetHeight() >= 0) )
	{
		return result;
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

	
	
	IndexMaskPtr mask = std::make_shared<IndexMask>();
	mask->SetMask( buf, size, w, h );
	free(buf);
	result = std::make_shared<ImageInfo>(mask, mPalette);

	if (!result->IsOk())
	{
		result = nullptr;
	}
	return result;
}



bool ImageInfo::PasteImageInfo( const wxPoint& point, ImageInfoPtr src )
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
	ImageInfoPtr newBuffered = CopyToImageInfo( rect );
	bool res = newBuffered->IsOk();

	if (res)
	{
		sBuffered = newBuffered;
		
		wxBitmap* bmp = sBuffered->GetBitmap();
		Helpers::CopyToClipboard(bmp->ConvertToImage());
		delete bmp;
	}

	return res;
}



//////////////////////////////////////////////////////////////////////////



ImageInfoDataObject::ImageInfoDataObject( ImageInfoPtr info ):
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
}



ImageInfoPtr ImageInfoDataObject::GetInfo() const
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

	mIndexMask = std::make_shared<IndexMask>();
	mPalette = std::make_shared<Palette>();

	bool res = IInfo::LoadState( input, version ) &&
		mIndexMask->LoadFromStream(input) && mPalette->LoadFromStream(input);

	if (!res)
	{
		Clear();
	}

	return res;
}
