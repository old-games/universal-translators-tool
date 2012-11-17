/***************************************************************
 * Name:      thumbnail.cpp
 * Purpose:   modified DrawPanel for proccess icon clicks
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-15
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "thumbnail.h"

ThumbnailPanel::ThumbnailPanel(  int number, wxWindow* parent ):
	DrawPanel( parent ),
	mInfontNumber( number ),
	mIsActive( false )
{
}



ThumbnailPanel::~ThumbnailPanel(void)
{
}



/* virtual */ void ThumbnailPanel::Render(wxDC& dc)
{
	if (!IsOk())
	{
		return;
	}
	mDrawFocus = !mIsActive;
	DrawPanel::Render( dc );

	if (mIsActive)
	{
		DrawRectAround( dc, *wxGREEN );
	}
}



/* virtual */ bool ThumbnailPanel::MouseButton( int btn, bool up )
{

	if ( DrawPanel::MouseButton( btn, up ) )
	{
		return true;
	}

	if (!up)
	{
		SymbolSelectionEvent event(mInfontNumber);
		wxTheApp->QueueEvent( event.Clone() );
	}
	return false;
}



/* virtual */ bool ThumbnailPanel::MouseModifiersButton( int modifier, int btn, bool up )
{
	if ( DrawPanel::MouseModifiersButton( modifier, btn, up ) )
	{
		return true;
	}
	return false;
}



/* virtual */ bool ThumbnailPanel::MouseMoving( int modifier, int btn )
{
	if ( DrawPanel::MouseMoving( modifier, btn ) )
	{
		return true;
	}
	return false;
}



