/***************************************************************
 * Name:      palette.h
 * Purpose:   Palette container declaration
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-14
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef PALETTE_H_INCLUDED
#define PALETTE_H_INCLUDED

class Palette
{
public:

	enum BPP
	{
		bppMono,
		bpp2,
		bpp4,
		bpp8,
		bpp15,	// http://en.wikipedia.org/wiki/High_color
		bpp16,	//
		bpp24,
		bpp32,
		bppNum
	};
	
	enum SourceFormat
	{
		sfNone,
		sfPlain,
		sfBMP,
		sfNum
	};

	Palette();
	Palette( const Palette& other );
	~Palette();
	Palette* Clone() { return new Palette(*this); }

	// bpp - required parameter
	// src - pointer to paletter buffer or NULL to use default
	// fmt - format of data stored in src
	// shift - some palettes need to shit each RGB value to left by 2
	bool		Initiate( BPP bpp, char* src = NULL, SourceFormat fmt = sfPlain, bool shift = false );
	bool		ChangeBPP(BPP bpp);
	void		SetCGAType( int cga, bool intensity );


	inline bool		IsOk() const;
	inline bool		IsIndexed();
	int				GetPalType() { return mBPP; }
	wxBitmap*		GeneratePalBitmap();
	void			GetColourByIndex( unsigned char n, char& r, char& g, char& b ) const;
	UttColour		GetColourByIndex( unsigned char n );
	UttColour		GetColourByCoordinates( const wxPoint& pos);
	wxPoint			GetIndexCoordinates( unsigned char n );
	int				GetCGAType() { return mCurrentCGAPal; }
	bool			GetIntensity() { return mCGAIntensity; }
	unsigned int	GetCorrectImageSize( int width, int height, bool forIndexMask = false );
	unsigned int	GetPaletteSize( BPP bits, SourceFormat fmt );

	
	// available static constants
	static const int		ColourNumber[bppNum];
	static const int		Bits[bppNum];
	static const wxString	Names[bppNum];
	static const wxSize		BitmapSize[bppNum];
	static const wxDouble	BitmapScale[bppNum];

	static size_t PaletteSize( int n );
	
private:

	void ShiftPalette();
	void CopyPalette( void* dest, void* src, bool skipFourth = false );
	void AllocateDatas();
	void ClearDatas();
	void ConvertHighColour2RGB( unsigned short i, unsigned char& r, unsigned char& g, unsigned char& b );


	int		mBPP;
	size_t	mSize;
	bool	mShifted;
	bool	mInitiated;
	bool	mCGAIntensity;
	int		mCurrentCGAPal;


	void*	mData;
	void*	mCurrent;

};


#endif	// PALETTE_H_INCLUDED
