#include "pch.h"
#include "uttypes.h"


const int BPP::ColourNumber[BPP::bppNum] =
{
	2,
	4,
	16,
	256,
	65536,
	16777216,
	16777216
};

const int BPP::Bits[BPP::bppNum] =
{
	1,
	2,
	4,
	8,
	16,
	24,
	32
};

const wxString BPP::Names[BPP::bppNum] =
{
	"Monochrome",
	"CGA",
	"EGA",
	"VGA",
	"High color",
	"True color",
	"True color with alpha"
};

SymbolInfo FontInfo::sBadSymbol;

void SymbolInfo::SetValues(wxInt32 width, wxInt32 height, wxUint32 code, const char* data /* NULL */)
{
	mWidth = width;
	mHeight = height;
	mCode = code;
	if (data != NULL)
	{
		CreateData();
		memcpy(mData, data, sizeof( LetterBox ));
	}
	else
	{
		EraseData();
	}
}

inline SymbolInfo &SymbolInfo::operator = ( const SymbolInfo &src )
{
	this->SetValues(src.mWidth, src.mHeight, src.mCode, (char*) src.mData);
	return *this;
}

void SymbolInfo::SetData(const char* data /* NULL */)
{
}

inline void SymbolInfo::CreateData()
{
	if (mData == NULL)
	{
		static const size_t size = sizeof(LetterBox);
		mData = new LetterBox[size];
		memset( mData, 0, size );
	}
}

inline void SymbolInfo::EraseData()
{
	delete[] mData;
	mData = NULL;
}

LetterBox* SymbolInfo::GetData()
{
	CreateData();
	return mData;
}

inline int SymbolInfo::BoxOffset(int x, int y)
{
	wxInt32 offset = (x * MAXIMUM_SYMBOL_WIDTH) + y;
	if ( (size_t) offset >= sizeof(LetterBox) )
	{
		wxLogMessage( wxString::Format("SymbolInfo::BoxOffset: coordinates are out of range (X: %d, Y: %d)", x, y) );
		return -1;
	}
	return offset;
}

void SymbolInfo::SetPixel( int x, int y, RGBA color )
{
	int offset = BoxOffset(x, y);
	if ( offset < 0 )
	{
		return;
	}
	Pixel& val = *mData[offset];
	val[0] = color.R;
	val[1] = color.G;
	val[2] = color.B;
}

RGBA SymbolInfo::GetPixel( int x, int y )
{
	RGBA res;
	int offset = BoxOffset(x, y);
	if ( offset < 0 )
	{
		return res;
	}
	Pixel& val = *mData[offset];
	res.R = val[0];
	res.G = val[1];
	res.B = val[2];
	return res;
}




void FontInfo::SetValues( int maxHeight, int minHeight, int maxWidth, int minWidth,
				int bpp /* BPP::bppMono */,
				int fontCodePage /* wxFONTENCODING_DEFAULT */,
				int baseLine /* 0 */,
				int capLine /* 0 */,
				int lowLine /* 0 */)
{
	mMaxWidth = maxWidth;
	mMaxHeight = maxHeight;
	mMinWidth = minWidth;
	mMinHeight = minHeight;
	mBPP = bpp;
	mFontCodePage = fontCodePage;
	mBaseLine = baseLine;
	mCapLine = capLine;
	mLowLine = lowLine;
}



void FontInfo::SetSymbolsNum(size_t n)
{
	if (n >= MINIMUM_SYMBOLS_NUM)
	{
		mSymbols.resize(n);
	}
}

