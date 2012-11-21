/***************************************************************
 * Name:      helpers.cpp
 * Purpose:   Code for helpers 
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-14
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "helpers.h"
#include "types/palette.h"

namespace Helpers
{

wxWindowID wxCustomPanelId = wxID_HIGHEST + 1024;



wxBitmap* CreateBitmap( Pixel* buffer, int width, int height )
{
	wxImage image( width, height, (wxByte*) buffer, true );
	return new wxBitmap( image );
}


bool CopyToClipboard( const wxImage& img )
{
	bool res = false;
	if ( img.IsOk() && wxTheClipboard->Open() )
	{
		wxBitmapDataObject* obj = new wxBitmapDataObject( wxBitmap( img ) );
		res = wxTheClipboard->SetData( obj );
		wxTheClipboard->Close();
	}
	else
	{
		wxLogError("Helpers::CreateDataObject: There was an error while trying to copy to the clipboard!");
	}
	return res;
}



bool CopyToClipboard( const wxRect& rect, const wxBitmap* bmp )
{
	wxImage img = bmp->ConvertToImage().GetSubImage( rect );
	return CopyToClipboard( img );
}



void Buffer8bpp_to_Pixels(Pixel* dst, int dstWidth, int dstHeight, const char* src, int srcWidth, int srcHeight, const Palette* pal )
{
	memset( dst, 0, dstWidth * dstHeight * sizeof( Pixel ) );
	size_t copyLength = sizeof( Pixel ) * dstWidth;
	int correction = dstWidth - srcWidth;
	for (int  y = 0; y < srcHeight; ++y)
	{
		for (int x = 0; x < srcWidth; ++x)
		{
			Pixel& p = *dst;
			pal->GetColourByIndex(*src, p[0], p[1], p[2]);
			++dst;
			++src;
		}
		//dst += correction;
	}


}

} // namespace Helpers