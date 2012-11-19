/***************************************************************
 * Name:      indexmask.h
 * Purpose:   Mask container for Bitmap with indexed palette
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-18
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef INDEXMASK_H_INCLUDED
#define INDEXMASK_H_INCLUDED

// forward declarations
class Palette;
class IndexMask;

class IndexMask
{
public:

	IndexMask() : 
		mWidth(0), 
		mHeight(0), 
		mSize(0), 	
		mSrcWidth( 0 ),
		mSrcHeight( 0 ), 
		mMask(NULL) {}

	IndexMask( const IndexMask& other );
	~IndexMask();
	
	bool WriteIndex( const wxPoint& pos, int n );
	int ReadIndex( const wxPoint& pos );

	void SetMask( const char* mask, int width, int height, int srcWidth = -1, int srcHeight = -1 );

	bool IsOk() { return mMask != NULL; }
	wxBitmap* GetBitmap( Palette* pal );
	IndexMask* Clone() const { return new IndexMask( *this ); }

private:
	void Clear();

	int				mWidth;
	int				mHeight;
	size_t			mSize;
	int				mSrcWidth;
	int				mSrcHeight;

	char*	mMask;
	
};


#endif	// INDEXMASK_H_INCLUDED
