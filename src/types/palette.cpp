/***************************************************************
 * Name:      palette.cpp
 * Purpose:   Palette container implementation
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-14
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "palette.h"



const int Palette::ColourNumber[bppNum] =
{
	2,
	4,
	16,
	256,
	32768,
	65536,
	16777216,
	16777216
};



const int Palette::Bits[bppNum] =
{
	1,
	2,
	4,
	8,
	15,
	16,
	24,
	32
};



const wxString Palette::Names[bppNum] =
{
	"Monochrome",
	"CGA",
	"EGA",
	"VGA",
	"High color (15bits)",
	"High color (16bits)",
	"True color",
	"True color with alpha"
};



size_t Palette::PaletteSize( int n )
{
	wxASSERT( n < bppNum );
	return ColourNumber[n] * sizeof(Pixel);
}



const wxSize	Palette::BitmapSize[bppNum] =
{
	wxSize(2, 1),		// Mono 2 colours
	wxSize(4, 1),		// CGA 4 colours
	wxSize(8, 2),		// EGA 16 colours
	wxSize(32, 8),		// VGA/SVGA	256 colours
	wxSize(256, 128),	// Highcolor (15bits) 32768 colours
	wxSize(256, 256),	// Highcolor 65536 colours
	wxSize(512, 512),	// Truecolor 16 777 216 colours
	wxSize(512, 512)	// Truecolor with alpha
};

const wxDouble Palette::BitmapScale[bppNum] =
{
	50.0f,
	40.0f,
	25.0f,
	20.0f,
	4.0f,
	3.0f,
	3.0f,
	3.0f
};



Palette::Palette():
	mBPP( bppMono ),
	mSize( 0 ),
	mShifted( false ),
	mInitiated( false ),
	mCGAIntensity( false ),
	mCurrentCGAPal( 0 ),
	mData( NULL ),
	mCurrent( NULL )
{
}



Palette::Palette( const Palette& other ):
	mBPP( other.mBPP ),
	mSize( other.mSize ),
	mShifted( other.mShifted ),
	mInitiated( other.mInitiated ),
	mCGAIntensity( other.mCGAIntensity ),
	mCurrentCGAPal( other.mCurrentCGAPal ),
	mData( NULL ),
	mCurrent( NULL )
{
	AllocateDatas();
	{	
		CopyPalette( mData, other.mData );
		CopyPalette( mCurrent, other.mCurrent );
	}
}



Palette::~Palette()
{
	ClearDatas();
}



bool Palette::IsOk() const
{
	return mInitiated;
}



bool Palette::IsIndexed()
{
	return mBPP <= bpp8;
}


void Palette::GetColourByIndex( unsigned char n, unsigned char& r, unsigned char& g, unsigned char& b ) const
{
	wxASSERT( IsOk() && n < ColourNumber[mBPP] );
	Pixel& p = ((Pixel*) mCurrent)[n];
	r = p[0];
	g = p[1];
	b = p[2];
}



UttColour Palette::GetColourByIndex( unsigned char n )
{
	unsigned char r, g, b;
	GetColourByIndex(n, r, g, b);
	return UttColour( wxColour(r, g, b), n );
}



UttColour Palette::GetColourByCoordinates( const wxPoint& pos)
{
	int n = (pos.y * BitmapSize[mBPP].x) + pos.x;
	return GetColourByIndex(n);
}



wxPoint	Palette::GetIndexCoordinates( unsigned char n )
{
	wxASSERT( n < ColourNumber[mBPP] );
	int y = n / BitmapSize[mBPP].x;
	return wxPoint( n - (y * BitmapSize[mBPP].x), y );
}



bool Palette::Initiate( BPP bpp, char* src /* NULL */, SourceFormat fmt /* sfPlain */, bool shift /* false */ )
{
	if (mInitiated)
	{
		return false;
	}

	mInitiated = false;
	if (bpp >= bppNum)
	{
		return false;
	}
	
	mBPP = bpp;
	mShifted = shift;
	
	switch (fmt)
	{
		case sfPlain:
			mSize = PaletteSize(bpp);
		break;
	}
	
	if (src == NULL)
	{
		switch( mBPP )
		{
			case bppMono:
				src = (char*) sMonoPal;
			break;

			case bpp2:
				src = mCGAIntensity ? (char*) sICGApal[ mCurrentCGAPal ] : (char*) sCGApal[ mCurrentCGAPal ];
			break;

			case bpp4:
			case bpp8:
				src = (char*) sVGApal;
			break;
		}
	}
	
	mInitiated = true;

	AllocateDatas();
	if ( this->IsIndexed() )
	{
		CopyPalette( mData, src );
		CopyPalette( mCurrent, src );
	}

	if (mShifted)
	{
		ShiftPalette();
	}
	return true;
}



void Palette::ShiftPalette()
{
	if (!this->IsOk() || !this->IsIndexed())
	{
		return;
	}

	Pixel* pal = (Pixel*) mCurrent;
	for (int i = 0; i < ColourNumber[mBPP]; ++i)
	{
		(*pal)[0] <<= 2;
		(*pal)[1] <<= 2;
		(*pal)[2] <<= 2;
		++pal;
	}
}



void Palette::CopyPalette( void* dest, void* src )
{
	if ( !IsOk() )
	{
		return;
	}
	memcpy(dest, src, mSize);
}



inline void Palette::ClearDatas()
{
	if (mData != NULL)
	{
		free(mData);
		mData = NULL;
	}
	
	if (mCurrent != NULL)
	{
		free(mCurrent);
		mCurrent = NULL;
	}
}



inline void Palette::AllocateDatas()
{
	ClearDatas();

	if ( this->IsOk() && this->IsIndexed() )
	{
		mData = malloc( mSize );
		mCurrent = malloc( mSize );
	}
}



bool Palette::ChangeBPP(BPP bpp)
{
	wxASSERT( bpp < bppNum );

	if (bpp == mBPP)
	{
		return mInitiated;
	}

	ClearDatas();
	mInitiated = false;
	return Initiate(bpp);
}



void Palette::SetCGAType( int cga, bool intensity )
{
	wxASSERT( cga < CGA_PALS_NUMBER );
	mCurrentCGAPal = cga;
	mCGAIntensity = intensity;
	mInitiated = false;
	mBPP = bppMono;
	ChangeBPP( bpp2 );
}



wxBitmap* Palette::GeneratePalBitmap()
{
	if (!IsOk())
	{
		return NULL;
	}
	
	const wxSize& size = BitmapSize[ mBPP ];
	
	const size_t bufSize = size.x * size.y;
	
	Pixel* colorMap = new Pixel[ bufSize ];
	Pixel* srcPal = (Pixel*) sVGApal;
	
	if ( this->IsIndexed() )
	{
		memcpy( colorMap, mCurrent, ColourNumber[ mBPP ] * sizeof(Pixel) );
	}
	else
	if ( mBPP > bpp16 )
	{
		Pixel* dstPal = colorMap;
		for (int y = 0; y < size.y; ++y)
		{
			Pixel& pix = * (srcPal++) ;
			wxColour col( pix[0], pix[1], pix[2] );
			for (int x = 0; x < size.x; ++x)
			{
				float perc = (float) x / (float) size.x;
				int lightness =  (int) (perc * 100.0f);

				wxColour newCol = col.ChangeLightness( lightness );
				Pixel& dst = * (dstPal++) ;
				dst[0] = newCol.Red();
				dst[1] = newCol.Green();
				dst[2] = newCol.Blue();
			}
		}
	}
	else
	{
		Pixel* dstPal = colorMap;
		int startx = 0;
		int x = startx;
		int leftGreen = mBPP == bpp15 ? 3 : 2;
		int stepX = mBPP == bpp15 ? 64 : 128;
		for (int i = 0; i < ColourNumber[ mBPP ]; ++i)
		{
			unsigned char r = 0, g = 0, b = 0;
			ConvertHighColour2RGB(x, r, g, b);
			Pixel& dst = * (dstPal++) ;
			dst[0] = r << 3;
			dst[1] = g << leftGreen;
			dst[2] = b << 3;
			x += stepX;
			if (x >= ColourNumber[ mBPP ])
			{
				x = ++startx;
			}
		}
	}

	wxBitmap* bmp = Helpers::CreateBitmap( colorMap, size.x, size.y );
	delete[] colorMap;
	return bmp;
}



inline void Palette::ConvertHighColour2RGB( unsigned short i, unsigned char& r, unsigned char& g, unsigned char& b )
{
	if (mBPP == bpp15)
	{
		r = i >> 9;
		g = (i >> 5) & 0x1F;
		b = i & 0x1F;
	}
	else
	{
		r = i >> 10;
		g = (i >> 5) & 0x3F;
		b = i & 0x1F;
	}
}


