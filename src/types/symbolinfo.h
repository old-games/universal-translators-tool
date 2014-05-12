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



class SymbolInfo: public IStateStore
{
public:

	SymbolInfo();
	SymbolInfo( const SymbolInfo& other );

	virtual ~SymbolInfo();


	SymbolInfoPtr Clone() { return std::make_shared<SymbolInfo>(*this); }

	bool IsOk();

	IndexMaskPtr GetData();
	inline int GetWidth() const { return mWidth; }
	inline int GetHeight() const { return mHeight; }
	inline int GetCode() const { return mCode; }

	void SetData(IndexMaskPtr data);
	void SetValues(int width, int height, unsigned int code,
		IndexMaskPtr data = nullptr);
	void SetWidth( int w );
	void SetHeight( int h );
	void SetCode( int code ) { mCode = code; }

	//SymbolInfo &operator = ( const SymbolInfo &src );

protected:

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );

	wxInt32			mWidth;				// ширина символа
	wxInt32			mHeight;			// высота символа
	wxUint32		mCode;				// код символа, для пробела 32 и т.д.
	IndexMaskPtr	mData;

private:

};





#endif // SYMBOLINFO_H_INCLUDED
