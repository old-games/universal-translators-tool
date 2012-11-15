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
	mInfontNumber( number )
{
}

ThumbnailPanel::~ThumbnailPanel(void)
{
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
	//bool left = btn == wxMOUSE_BTN_LEFT;
	//bool right = btn == wxMOUSE_BTN_RIGHT;
	//if (mMousePoint.x == -1 || mMousePoint.y == -1 || PointInZone( mMousePoint ) || !this->HasFocus() )
	//{
	//	return false;
	//}
	//if (left || right)
	//{
	//	mCurrentColour = right ? gGlobalRightColour : gGlobalLeftColour;
	//}
	//if ( !up && ( left || right ) )
	//{
	//	return BeginDrawing();
	//}
	return false;
}

/* virtual */ bool ThumbnailPanel::MouseModifiersButton( int modifier, int btn, bool up )
{
	if ( DrawPanel::MouseModifiersButton( modifier, btn, up ) )
	{
		return true;
	}
	//bool left = btn == wxMOUSE_BTN_LEFT;
	//bool right = btn == wxMOUSE_BTN_RIGHT;
	//bool both = left && right;
	//bool findColour = !up && !both && modifier == wxMOD_SHIFT;
	//bool setColour =  !up && !both && modifier == wxMOD_ALT;
	//if ( findColour || setColour )
	//{
	//	wxColour colour;
	//	if ( mMousePoint.x != -1 && mMousePoint.y != -1 && GetPixel(mMousePoint, colour) )
	//	{
	//		ColourPickEvent* colourEvent = new ColourPickEvent( colour, btn,
	//			findColour ? ColourPickEvent::cpeFindThisColour : ColourPickEvent::cpeSetThisColour );
	//		wxEvtHandler::QueueEvent( colourEvent );
	//		return true;
	//	}
	//}
	return false;
}


/* virtual */ bool ThumbnailPanel::MouseMoving( int modifier, int btn )
{
	if ( DrawPanel::MouseMoving( modifier, btn ) )
	{
		return true;
	}
	//if ( this->HasFocus() && mBitmapRect.Contains( mMousePoint ) && mMousePoint != mPreviousPoint)
	//{
	//	mPreviousPoint = mCursor;
	//	mCursor = mMousePoint;
	//	if (!DoEdit())
	//	{
	//		PaintNow();
	//	}
	//	return true;
	//}
	return false;
}



