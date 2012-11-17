/***************************************************************
 * Name:      thumbnail.h
 * Purpose:   modified DrawPanel for proccess icon clicks
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-15
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef THUMBNAILPANEL_H_INCLUDED
#define THUMBNAILPANEL_H_INCLUDED

#include "drawpanel.h"

class ThumbnailPanel :
	public DrawPanel
{

public:

	ThumbnailPanel( int number, wxWindow* parent );
	virtual ~ThumbnailPanel(void);

	inline void SetActive(bool b = true) { mIsActive = b; }
	inline bool IsActive() { return mIsActive; }

protected:

	virtual bool MouseButton( int btn, bool up );
	virtual bool MouseModifiersButton( int modifier, int btn, bool up );
	virtual bool MouseMoving( int modifier, int btn );

	virtual void Render(wxDC& dc);

private:

	int		mInfontNumber;
	bool	mIsActive;
};



WX_DEFINE_ARRAY( ThumbnailPanel* , ThumbnailsArray );

#endif
