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

#include "istatestore.h"
// forward declarations
class IndexMask;

class SymbolInfo: public IStateStore
{
public:

	SymbolInfo();
	SymbolInfo( const SymbolInfo& other );

	virtual ~SymbolInfo();


	SymbolInfo* Clone() { return new SymbolInfo(*this); }

	bool IsOk();

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

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );

	wxInt32		mWidth;				// ширина символа
	wxInt32		mHeight;			// высота символа
	wxUint32	mCode;				// код символа, для пробела 32 и т.д.
	IndexMask*	mData;										

private:

	void	EraseData();
};

typedef wxVector<SymbolInfo> Symbols;



#endif // SYMBOLINFO_H_INCLUDED
