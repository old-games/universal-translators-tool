/***************************************************************
 * Name:      symbolinfo.h
 * Purpose:   declaration of SymbolInfo class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-07-02
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef SYMBOLINFO_H_INCLUDED
#define SYMBOLINFO_H_INCLUDED

// forward declarations
class IndexMask;

class SymbolInfo
{
public:

	SymbolInfo(): mWidth( 0 ), mHeight( 0 ), mCode( 0 ), mData( NULL ) {}
	SymbolInfo( const SymbolInfo& other ):
		mWidth( other.mWidth ),
		mHeight( other.mHeight ),
		mCode( other.mCode ),
		mData( NULL )
	{
		SetData(other.mData);
	}
	virtual ~SymbolInfo();


	SymbolInfo* Clone() { return new SymbolInfo(*this); }

	IndexMask* GetData();
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	int GetCode() { return mCode; }

	void SetData(const IndexMask* data = NULL);
	void SetValues(int width, int height, unsigned int code, IndexMask* data = NULL);
	void SetWidth( int w );
	void SetHeight( int h );
	void SetCode( int code ) { mCode = code; }

	SymbolInfo &operator = ( const SymbolInfo &src );

protected:

	wxInt32		mWidth;				// ширина символа
	wxInt32		mHeight;			// высота символа
	wxUint32	mCode;				// код символа, для пробела 32 и т.д.
	IndexMask*	mData;										

private:

	void	EraseData();
};

typedef wxVector<SymbolInfo> Symbols;



#endif // SYMBOLINFO_H_INCLUDED
