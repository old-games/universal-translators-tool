/***************************************************************
 * Name:      uttypes.h
 * Purpose:   UTT Types
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-01-24
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef UTTTYPES_H_INCLUDED
#define UTTTYPES_H_INCLUDED

#define MAXIMUM_SYMBOLS_NUM			16384
#define MINIMUM_SYMBOLS_NUM			1

#define MAXIMUM_SYMBOL_WIDTH		64
#define MAXIMUM_SYMBOL_HEIGHT		64


typedef wxByte Pixel[3];
typedef wxByte PixelA[4];



struct RGBA
{
	RGBA(): R(0), G(0), B(0), A(0xFF)	{};
	wxByte R;
	wxByte G;
	wxByte B;
	wxByte A;
};



namespace PalOwners
{
	enum
	{
		poFontEditor,
		poImageEditor,
		poNum
	};

	extern const wxString OwnerName[poNum];

	extern const wxWindowID OwnerID[poNum];
}

class UttColour: public wxColour
{
public:

	UttColour(): wxColour(), mIndex(-1) {}

	UttColour( const UttColour& col):
		wxColour(col),
		mIndex(col.mIndex) {}

	UttColour( const wxColour& col, int n = -1):
		wxColour(col),
		mIndex(n) {}

	inline int GetIndex() const { return mIndex; }
	inline void SetIndex(int n) { mIndex = n; }

	inline UttColour& operator = ( const wxColour &col )
	{
		this->SetRGBA(col.GetRGBA());
		this->mIndex = -1;
		return *this;
	}

	inline bool operator == ( const UttColour& col )
	{
		return this->mIndex == col.mIndex && this->GetRGBA() == col.GetRGBA();
	}

private:

	int mIndex;
};


#endif	// UTTTYPES_H_INCLUDED
