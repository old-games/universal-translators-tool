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
class ImageInfoDataObject;



class ImageInfo: public IInfo
{
public:
	ImageInfo();
	ImageInfo(IndexMaskPtr mask, PalettePtr pal);
	ImageInfo(const ImageInfo& other);

	~ImageInfo();
	ImageInfoPtr Clone() const { return std::make_shared<ImageInfo>(*this); }

	void SetImage(IndexMaskPtr mask);
	bool SetPalette(PalettePtr pal);
	void SetPaletteAsMain();
	
	bool		IsOk() const;
	IndexMaskPtr	GetImage() const { return mIndexMask; }
	PalettePtr		GetPalette() const { return mPalette; }
	wxBitmap*		GetBitmap() const;
	wxSize			GetSize() const;

	void		Clear();
	bool		CopyToClipBoard( const wxRect& rect );
	ImageInfoPtr	CopyToImageInfo( const wxRect& rect );
	bool			PasteImageInfo( const wxPoint& point, ImageInfoPtr src ) ;
	
	static const ImageInfoPtr	GetBuffered() { return sBuffered; }

protected:

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );

private:
	
	void	ClearImage();
	void	ClearPalette();

	IndexMaskPtr	mIndexMask;
	PalettePtr		mPalette;

	static	ImageInfoPtr	sBuffered;
};



//////////////////////////////////////////////////////////////////////////



class ImageInfoDataObject: public wxBitmapDataObject
{
public:
	ImageInfoDataObject( ImageInfoPtr mImageInfo );
	ImageInfoDataObject( const ImageInfoDataObject& other );
	~ImageInfoDataObject();
		
	ImageInfoPtr GetInfo() const;
private:

	ImageInfoPtr	mImageInfo;
};



#endif // IMAGEINFO_H_INCLUDED
