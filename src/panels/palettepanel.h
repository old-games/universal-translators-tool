/***************************************************************
 * Name:      palettepanel.h
 * Purpose:   PalettePanel has to be used to select colour
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-07
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef PALETTEPANEL_H_INCLUDED
#define PALETTEPANEL_H_INCLUDED

// TODO: remove when will be done
#include "editpanel.h"

class PaletteWindowImpl;
class Palette;

class PalettePanel :
	public EditPanel
{

friend class PaletteWindowImpl;

public:
	PalettePanel( wxWindow* parent, Palette* pal, bool changeGlobalColours = true );
	~PalettePanel();

	const wxColour& GetColour( bool right );

	void SetColour( bool right, const wxColour& colour );
	int	FindColour( bool right, const wxColour& colour, bool andSet = false );

protected:

	virtual void Render(wxDC& dc);

	virtual bool MouseButton( int btn, bool up );
	virtual bool KeyDown( int modifier, int keyCode );

private:

	void SetNewPalette( Palette* pal );
	void SetCurrentPalette( Palette* pal );
	Palette* GetCurrentPalette();

	void SetBitmapFromPalette();
	void GetBitmapColour( bool right );
	void SetBitmapColour( bool right );
	void CorrectColourPosition( bool right );
	void SetGlobalColours();
	

	wxPoint		mLeftPos;
	wxPoint		mRightPos;
	wxColour	mLeftColour;
	wxColour	mRightColour;
	bool		mChangeGlobals;
	bool		mContainerMode; 

	Palette*	mCurrentPal;

};

#endif
