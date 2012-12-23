/***************************************************************
 * Name:      imageinfo.h
 * Purpose:   declaration of ImageInfo class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-19
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef IMAGEINFO_H_INCLUDED
#define IMAGEINFO_H_INCLUDED

#include "iinfo.h"

// forward declarations
class IndexMask;
class Palette;
class ImageInfoDataObject;

class ImageInfo: public IInfo
{
public:
	ImageInfo();
	ImageInfo(IndexMask* mask, Palette* pal);
	ImageInfo( const ImageInfo& other );

	~ImageInfo();
	ImageInfo* Clone() const { return new ImageInfo(*this); }

	void SetImage( IndexMask* mask );
	bool SetPalette(Palette* pal);
	void SetPaletteAsMain();
	
	bool		IsOk() const;
	IndexMask*	GetImage() const { return mIndexMask; }
	Palette*	GetPalette() { return mPalette; }
	wxBitmap*	GetBitmap() const;
	wxSize		GetSize() const;

	void		Clear();
	bool		CopyToClipBoard( const wxRect& rect );
	ImageInfo*	CopyToImageInfo( const wxRect& rect );
	bool		PasteImageInfo( const wxPoint& point, const ImageInfo* src ) ;
	
	static void				Done() { delete sBuffered; sBuffered = NULL; }
	static const ImageInfo*	GetBuffered() { return sBuffered; }

protected:

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );

private:
	
	void	ClearImage();
	void	ClearPalette();

	IndexMask*		mIndexMask;
	Palette*		mPalette;

	static		ImageInfo*	sBuffered;
};



//////////////////////////////////////////////////////////////////////////



class ImageInfoDataObject: public wxBitmapDataObject
{
public:
	ImageInfoDataObject( const ImageInfo* mImageInfo );
	ImageInfoDataObject( const ImageInfoDataObject& other );
	~ImageInfoDataObject();
		
	ImageInfo* ImageInfoDataObject::GetInfo();
private:

	ImageInfo*	mImageInfo;
};



#endif // IMAGEINFO_H_INCLUDED
