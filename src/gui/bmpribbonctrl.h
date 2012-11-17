/***************************************************************
 * Name:      bmpribbonctrl.h
 * Purpose:   Bitmap ribbon control
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef BITMAPRIBBONCTRL_H_INCLUDED
#define BITMAPRIBBONCTRL_H_INCLUDED

#include "simplegui.h"

class ThumbnailsArray;

class BitmapRibbonCtrl : public BitmapRibbonGui
{
public:
	BitmapRibbonCtrl( wxWindow* parent );
	~BitmapRibbonCtrl(void);

	void Clear();
	void SetBitmap( size_t n, wxBitmap* bmp );

	void RefillHolder( bool recalcCount = true );
	void DoIncrement( int step );

	void ActiveChanged( int old, int n );

protected:

	virtual void OnButtonClick( wxCommandEvent& event );
	virtual void OnSize( wxSizeEvent& event );

private:

	void CalculateThumbsCount( bool useSize = false, const wxSize& size = wxDefaultSize );

	ThumbnailsArray*	mThumbnails;
	size_t				mCurrent;
	size_t				mToShow;
};

#endif
