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

#include "istatestore.h"

class Palette: public IStateStore
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

	PalettePtr Clone() { return std::make_shared<Palette>(*this); }

	// bpp - required parameter
	// src - pointer to paletter buffer or NULL to use default
	// fmt - format of data stored in src
	// shift - some palettes need to shit each RGB value to left by 2
	bool		Initiate( BPP bpp, char* src = NULL, SourceFormat fmt = sfPlain, bool shift = false );
	bool		Initiate( BPP bpp, wxByte* src = NULL, SourceFormat fmt = sfPlain, bool shift = false );
	bool		ChangeBPP(BPP bpp);
	void		SetCGAType( int cga, bool intensity );


	inline bool		IsOk() const;
	inline bool		IsIndexed();
	int				GetPalType() { return mBPP; }
	wxBitmap*		GeneratePalBitmap();
	void			GetColourByIndex( unsigned char n, wxByte& r, wxByte& g, wxByte& b ) const;
	UttColour		GetColourByIndex( unsigned char n );
	UttColour		GetColourByCoordinates( const wxPoint& pos);
	wxPoint			GetIndexCoordinates( unsigned char n );
	int				GetCGAType() { return mCurrentCGAPal; }
	bool			GetIntensity() { return mCGAIntensity; }
	unsigned int	GetCorrectImageSize( int width, int height,
		bool forIndexMask = false ) const;
	unsigned int	GetPaletteSize( BPP bits, SourceFormat fmt ) const;

	void SetColourByIndex(unsigned n, wxByte r, wxByte g, wxByte b);
	void SetColourByIndex(const UttColour& colour);
	
	// available static constants
	static const unsigned	ColourNumber[bppNum];
	static const unsigned	Bits[bppNum];
	static const wxString	Names[bppNum];
	static const wxSize		BitmapSize[bppNum];
	static const wxDouble	BitmapScale[bppNum];

	static size_t PaletteSize( int n );

protected:

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );
	
private:

	void ShiftPalette();
	void CopyPalette( void* dest, void* src, bool skipFourth = false );
	void AllocateDatas();
	void ClearDatas();
	void ConvertHighColour2RGB( unsigned short i, unsigned char& r, unsigned char& g, unsigned char& b );


	wxInt32		mBPP;
	wxUint32	mSize;
	bool		mShifted;
	bool		mInitiated;
	bool		mCGAIntensity;
	wxByte		mCurrentCGAPal;


	void*	mData;
	void*	mCurrent;

};


#endif	// PALETTE_H_INCLUDED
