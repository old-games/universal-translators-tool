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

#include "iinfo.h"

// forward declarations
class Palette;
class IndexMask;
class ImageInfoDataObject;

class IndexMask: public IInfo
{
public:

	IndexMask();
	IndexMask( const IndexMask& other );
	~IndexMask();
	
	bool	WriteIndex( const wxPoint& pos, int n );
	int		ReadIndex( const wxPoint& pos );

	void SetMask( const char* charMask, int srcSize, 
		int width, int height, int srcWidth = -1, int srcHeight = -1 );
	void SetMask( const wxByte* mask, int srcSize, 
		int width, int height, int srcWidth = -1, int srcHeight = -1 );

	inline bool		IsOk() const { return mMask != NULL; }
	wxBitmap*		GetBitmap( PalettePtr pal ) const;
	const wxByte*	GetMask() const { return mMask; }
	int				GetWidth() const { return mWidth; }
	int				GetHeight() const { return mHeight; }

	IndexMaskPtr Clone() const { return std::make_shared<IndexMask>( *this ); }
	
	template<typename T>
	bool InsertMask( const wxPoint& point, IndexMaskPtr src ) const
	{	
		wxRect targetRect( point.x, point.y, src->GetWidth(), src->GetHeight() );
		wxRect checkRect = targetRect;
			
		if (checkRect.GetWidth() >= 0 && checkRect.GetHeight() >= 0)
		{
			char* newSrc = NULL;
			if (targetRect != checkRect.Intersect( wxRect(0, 0, mWidth, mHeight) ))
			{
				int w = checkRect.GetWidth();
				int h = checkRect.GetHeight();

				newSrc = (char*) malloc( w * h * sizeof(T));
 
				Helpers::CropBuffer<T>( (T*) newSrc, w, h, (const T*) src->GetMask(), src->GetWidth() );
				Helpers::InsertSubBuffer<T>( (T*) mMask, mWidth,  
						(const T*) newSrc, w, h,
						point.x, point.y);

				free(newSrc);
			}
			else
			{
				Helpers::InsertSubBuffer<T>( (T*) mMask, mWidth, 
						(const T*) src->GetMask(), checkRect.GetWidth(), checkRect.GetHeight(),
						point.x, point.y);
			}
			return true;
		}
		return false;
	}

protected:

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );

private:
	void Clear();

	wxInt32			mWidth;
	wxInt32			mHeight;
	wxUint32		mSize;
	wxInt32			mSrcWidth;
	wxInt32			mSrcHeight;

	wxByte*			mMask;
	
};

#endif	// INDEXMASK_H_INCLUDED
