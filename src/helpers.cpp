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
#include "luacontrol.h"

namespace Helpers
{

wxWindowID wxCustomPanelId = wxID_HIGHEST + 1024;



wxBitmap* CreateBitmap( Pixel* buffer, int width, int height )
{
	wxImage image( width, height, (wxByte*) buffer, true );
	return new wxBitmap( image );
}



void CropSubBuffer2(Pixel* dst, int dstWidth, int dstHeight, const Pixel* src, int srcWidth, int cx, int cy)
{
	memset( dst, 0, dstWidth * dstHeight * sizeof( Pixel ) );
	size_t copyLength = sizeof( Pixel ) * dstWidth;
	src += (cy * srcWidth) + cx;
	for (int  y = 0; y < dstHeight; ++y)
	{
		memcpy(dst, src, copyLength);
		dst += dstWidth;
		src += srcWidth;
	}
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



void Buffer8bpp_to_Pixels(Pixel* dst, int dstWidth, int dstHeight, const wxByte* src, int srcWidth, int srcHeight, const Palette* pal )
{
	memset( dst, 0, dstWidth * dstHeight * sizeof( Pixel ) );
	//size_t copyLength = sizeof( Pixel ) * dstWidth;
	//int correction = dstWidth - srcWidth;
	for (int  y = 0; y < srcHeight; ++y)
	{
		for (int x = 0; x < srcWidth; ++x)
		{
			Pixel& p = *dst;
			pal->GetColourByIndex(*src, p[0], p[1], p[2]);
			++dst;
			++src;
		}
	}
}


// at the current moment works only with width multiple of four
// correction number is ((3 * w) % 4)*bytespp, but IndexMask don't understand it 
void BufferToBMPStyle(wxByte* mask, int w, int h, int bytespp)
{
	int realWidth = w * bytespp;
	int step = -realWidth;

	size_t size = w * h * bytespp;
	wxByte* dest = (wxByte*) malloc(size);
	wxByte* src = mask + ( realWidth * (h - 1) );

	for (int y = 0; y < h; y++)
	{
		memcpy( dest, src, realWidth );
		dest += realWidth;
		src += step;
	}
	dest -= size;
	memcpy( mask, dest, size);
	free(dest);
}



bool PullTableOfStrings( wxArrayString& res, lua_State* L /* NULL */)
{
	res.Clear();

	if ( L == NULL )
	{
		L = Lua::Get().get_ptr();
	}

	OOLUA::Lua_table modules;

	if (!OOLUA::pull2cpp(L, modules))
	{
		return false;
	}

	int count = 1;
	std::string value;

	while (modules.safe_at( count++, value ))
	{
		res.Add( wxString(value) );
	}

	return true;
}



void PullStringArguments( wxArrayString& res, lua_State* L /* NULL */)
{
	res.Clear();

	if ( L == NULL )
	{
		L = Lua::Get().get_ptr();
	}
	
	std::string txt;
	
	while(OOLUA::pull2cpp(L, txt))
	{
		res.Insert(txt, 0);
	}
}

} // namespace Helpers
