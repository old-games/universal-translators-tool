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

// forward declarations
class IndexMask;
class Palette;

class ImageInfo
{
public:
	ImageInfo();
	ImageInfo( const ImageInfo& other );

	~ImageInfo();
	ImageInfo* Clone() { return new ImageInfo(*this); }

	void SetImage( IndexMask* mask );
	bool SetPalette(Palette* pal);
	
	IndexMask* GetImage() { return mIndexMask; }
	Palette* GetPalette() { return mPalette; }

protected:

private:
	
	void	ClearImage();
	void	ClearPalette();

	IndexMask*		mIndexMask;
	Palette*		mPalette;
};



#endif // IMAGEINFO_H_INCLUDED
