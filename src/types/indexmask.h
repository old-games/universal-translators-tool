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
class ImageInfoDataObject;

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
	
	bool	WriteIndex( const wxPoint& pos, int n );
	int		ReadIndex( const wxPoint& pos );

	/*template<typename T>
	bool	InsertMask( const wxPoint& point, const IndexMask* src ) const;*/

	void SetMask( const char* mask, int srcSize, int width, int height, int srcWidth = -1, int srcHeight = -1 );

	bool		IsOk() { return mMask != NULL; }
	wxBitmap*	GetBitmap( Palette* pal );
	const char* GetMask() const { return mMask; }
	int			GetWidth() const { return mWidth; }
	int			GetHeight() const { return mHeight; }

	IndexMask* Clone() const { return new IndexMask( *this ); }
	
	template<typename T>
	bool InsertMask( const wxPoint& point, const IndexMask* src ) const
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
