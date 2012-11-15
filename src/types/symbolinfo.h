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


struct SymbolInfo
{

	SymbolInfo():
		mWidth( 0 ),
		mHeight( 0 ),
		mCode( 0 ),
		mData( NULL )
	{
	}

	SymbolInfo( const SymbolInfo& other ):
	mWidth( other.mWidth ),
	mHeight( other.mHeight ),
	mCode( other.mCode ),
	mData( NULL )
	{
		SetData(other.mData);
	}

	RGBA GetPixel( int x, int y );
	void SetPixel( int x, int y, RGBA color );

	virtual ~SymbolInfo();

	LetterBox* GetData();
	void SetData(const LetterBox* data = NULL);

	void SetValues(int width, int height, unsigned int code, LetterBox* data = NULL);

	SymbolInfo &operator = ( const SymbolInfo &src );

	wxInt32	mWidth;											// ширина символа
	wxInt32 mHeight;										// высота символа
	wxUint32 mCode;											// код символа, для пробела 32 и т.д.

protected:

	LetterBox* mData;										// данные символа, в protected - для
															// контроля за инициализацией

private:

	void CreateData();
	void EraseData();
	int BoxOffset(int x, int y);
};

typedef wxVector<SymbolInfo> Symbols;



#endif // SYMBOLINFO_H_INCLUDED
