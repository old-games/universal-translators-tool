/***************************************************************
 * Name:      palettepanel.cpp
 * Purpose:   Code for PalettePanel Class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-07
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "types/palette.h"
#include "palettepanel.h"



PalettePanel::PalettePanel(  wxWindow* parent, PalettePtr pal, wxWindowID eventsId /* wxID_ANY */):
	EditPanel( parent, eventsId ),
		mLeftPos(0, 0),
		mRightPos(1, 0),
		mContainerMode( pal != NULL ),
		mCurrentPal( pal )
{
	SetAllowScaling( false );
	SetAllowEdit( false );
	SetDrawFocus( false );
	SetAlign( utdHCenter | utdVCenter );
	SetBitmapScale( 12.0f );
	SetGridEnabled();
	SetGridLogic( wxCOPY );

	if (!mContainerMode)
	{
		mCurrentPal = std::make_shared<Palette>();
		mCurrentPal->Initiate( Palette::bppMono, (wxByte*) NULL  );
		SetBitmapFromPalette();
	}
	else
	{
		mCurrentPal = pal;	
	}
}



PalettePanel::~PalettePanel(void)
{
}



void PalettePanel::SetNewPalette(PalettePtr pal)
{
	if (mContainerMode)
	{
		wxLogError( "PalettePanel::SetNewPalette: palette panel is not in \"conainer\". Use SetNewPalette instead!");
		return;
	}

	mCurrentPal = pal->Clone();
}



void PalettePanel::SetCurrentPalette( PalettePtr pal )
{
	if (!mContainerMode)
	{
		wxLogError( "PalettePanel::SetCurrentPalette: palette panel is not in \"conainer\". Use SetNewPalette instead!");
		return;
	}

	if (pal->IsOk())
	{
		mCurrentPal = pal;
	}
}



void PalettePanel::SetBitmapFromPalette()
{
	if (!mCurrentPal->IsOk())
	{
		return;
	}

	SetBitmap( mCurrentPal->GeneratePalBitmap() );
	SetGridEnabled( mCurrentPal->IsIndexed() );
	CorrectColourPosition( false );
	CorrectColourPosition( true );
	SetBitmapScale( Palette::BitmapScale[ mCurrentPal->GetPalType() ] );
}



void PalettePanel::CorrectColourPosition( bool right )
{
	wxPoint& pos = right ? mRightPos : mLeftPos;
	if (pos.x >= mBitmap->GetWidth())
	{
		pos.x = mBitmap->GetWidth() - 1;
	}
	if (pos.y >= mBitmap->GetHeight())
	{
		pos.y = mBitmap->GetHeight() - 1;
	}

	GetBitmapColour( right );
}



void PalettePanel::GetBitmapColour( bool right )
{
	UttColour& colour = right ? mRightColour : mLeftColour;
	wxPoint& pos = right ? mRightPos : mLeftPos;

	if (mCurrentPal->IsIndexed())
	{
		colour = mCurrentPal->GetColourByCoordinates(pos);
	}
	else	
	{
		this->GetPixel( pos , colour );
	}
	this->GetParent()->Refresh();


	EditorRebuildDataEvent* event = new EditorRebuildDataEvent(mEventsId, 
		EditorRebuildDataEvent::whEditColourChanged, &colour, right);
	wxTheApp->QueueEvent( event );
}



void PalettePanel::SetBitmapColour( bool right )
{
	UttColour& colour = right ? mRightColour : mLeftColour;
	wxPoint& pos = right ? mRightPos : mLeftPos;
	DoPlacePixel( pos, colour );
}



const UttColour& PalettePanel::GetColour( bool right )
{
	return right ? mRightColour : mLeftColour;
}



void PalettePanel::SetColour( bool right, const UttColour& colour)
{
	if (right)
	{
		mRightColour = colour;
	}
	else
	{
		mLeftColour = colour;
	}
	SetBitmapColour( right );
}



int	PalettePanel::FindColour( bool right, const UttColour& colour, bool andSet /* false */ )
{
	int res = -1;
	wxPoint pos( -1, -1 );

	if (colour.GetIndex() == -1)
	{
		wxMemoryDC temp_dc;
		temp_dc.SelectObject(*mBitmap);
		wxColour compare;
		for ( int y = 0; y < mHeight && res == -1; ++y )
		{
			for ( int x = 0; x < mWidth; ++x )
			{
				if ( temp_dc.GetPixel( x, y, &compare ) && compare == colour )
				{
					res = (y * mWidth) + x;
					pos.x = x;
					pos.y = y;
					break;
				}
			}
		}
	}
	else
	{
		res = colour.GetIndex();
		pos = mCurrentPal->GetIndexCoordinates( res ); 
	}

	if (res != -1 && andSet)
	{
		if ( right )
		{
			mRightPos = pos;
		}
		else
		{
			mLeftPos = pos;
		}
		GetBitmapColour( right );
	}
	return res;
}



/* virtual */ void PalettePanel::Render(wxDC& dc)
{
	EditPanel::Render( dc );
	wxSize size( mRealScale + 2, mRealScale + 2);
	dc.SetBrush( *wxTRANSPARENT_BRUSH );
	dc.SetLogicalFunction( wxCOPY );
	wxPen pen( *wxGREEN, 3, wxPENSTYLE_LONG_DASH );
	for (int i = 0; i < 2; ++i)
	{
		wxPoint pos = i == 0 ? mLeftPos : mRightPos;
		wxPoint from( (pos.x * mRealScale) - 1, (pos.y * mRealScale) - 1 );
		if ( i > 0 )
		{
			pen.SetColour( *wxRED );
			if (mLeftPos == mRightPos)
			{
				from.x -= 2;
				from.y -= 2;
				size += wxSize(4, 4);
			}
		}
		dc.SetPen( pen );
		dc.DrawRectangle( from, size );
	}
}



void PalettePanel::SetColourPosition( const wxPoint& pos, bool right )
{
	if ( right )
	{
		mRightPos = pos;
	}
	else
	{
		mLeftPos = pos;
	}

	GetBitmapColour( right );
}



/* virtual */ bool PalettePanel::MouseButton( int btn, bool up )
{
	if ( EditPanel::MouseButton( btn, up ) )
	{
		return true;
	}

	if ( up && mBitmapRect.Contains( mMousePoint) && ( btn != wxMOUSE_BTN_LEFT || btn != wxMOUSE_BTN_RIGHT ) )
	{
		return false;
	}

	if (IsMousePointOk())
	{
		SetColourPosition( mMousePoint, btn == wxMOUSE_BTN_RIGHT );
	}
	return true;
}



/* virtual */ bool PalettePanel::KeyDown( int modifier, int keyCode )
{
	if ( EditPanel::KeyDown( modifier, keyCode ) )
	{
		return true;
	}
	bool res = true;
	switch ( keyCode )
	{
		case WXK_NUM_ONE:
			mLeftPos = mCursor;
		break;

		case WXK_NUM_TWO:
			mRightPos = mCursor;
		break;

		default:
			res = false;
	}
	if (res)
	{
		GetBitmapColour( keyCode == WXK_NUM_TWO );
		PaintNow();
	}
	return res;
}
