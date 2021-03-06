/***************************************************************
 * Name:      symbolpanel.cpp
 * Purpose:   Code for SymbolPanel class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-14
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"

#include "types/fontinfo.h"
#include "types/imageinfo.h"
#include "panels/symbolpanel.h"
#include "panels/controlline.h"


SymbolPanel::SymbolPanel(wxWindow* parent, wxWindowID eventsId /* wxID_ANY */):
	EditPanel( parent, eventsId ),
		mFontInfo(),
		mAllowEdit( true ),
		mSymbolNumber( 0 ),
		mActiveLine( -1 ),
		mDragLine( false ),
		mDragPoint( -1, -1 )
{
	for (int i = 0; i < clNum; ++i)
	{
		mLines[i] = new ControlLine( this );
	}
}



SymbolPanel::~SymbolPanel(void)
{
	for (int i = 0; i < clNum; ++i)
	{
		delete mLines[i];
	}
}



void SymbolPanel::SetFontInfo( FontInfoPtr info, int symbolNumber )
{
	mFontInfo = info;
	mSymbolNumber = symbolNumber;
	UpdateBitmap();
	UpdateControlLines();
}



void SymbolPanel::UpdateBitmap()
{
	if ( !mFontInfo )
	{
		DestroyBitmap();
		return;
	}

	SymbolInfoPtr sym = mFontInfo->GetSymbol( mSymbolNumber );

	if (!sym)
	{
		wxLogMessage( wxString::Format("SymbolPanel::UpdateBitmap: can't update bitmap for symbol %d", mSymbolNumber) );
		return;
	}

	ImageInfoPtr img = std::make_shared<ImageInfo>(sym->GetData(),
		mFontInfo->GetPalette());
	this->SetIndexedBitmap(img, false );
}



void SymbolPanel::UpdateControlLines()
{
	SymbolInfoPtr sym = mFontInfo->GetSymbol( mSymbolNumber );

	mLines[ clSymbolWidth ]->SetParameters( wxVERTICAL, *wxRED, 3, wxSOLID, "Symbol width" );
	mLines[ clSymbolWidth ]->SetValue( sym->GetWidth());

	mLines[ clSymbolHeight ]->SetParameters( wxHORIZONTAL, *wxBLUE, 3, wxSOLID, "Symbol height" );
	mLines[ clSymbolHeight ]->SetValue( sym->GetHeight() );

	mLines[ clBaseLine ]->SetParameters( wxHORIZONTAL, *wxGREEN, 3, wxSHORT_DASH, "Font base line" );
	mLines[ clBaseLine ]->SetValue( mFontInfo->GetBaseLine() );

	mLines[ clCapLine ]->SetParameters( wxHORIZONTAL, *wxGREEN, 3, wxSHORT_DASH, "Font capitals line" );
	mLines[ clCapLine ]->SetValue( mFontInfo->GetCapLine() );

	mLines[ clLowLine ]->SetParameters( wxHORIZONTAL, *wxGREEN, 3, wxSHORT_DASH, "Font lows line" );
	mLines[ clLowLine ]->SetValue( mFontInfo->GetLowLine() );
}

/* virtual */ void SymbolPanel::Render( wxDC& dc )
{
	EditPanel::Render( dc );
	for (int i = 0; i < clNum; ++i)
	{
		mLines[i]->DrawControlLine( dc );
	}
}

/* virtual */ void SymbolPanel::SetShowParams()
{
	EditPanel::SetShowParams();

	for (int i = 0; i < clNum; ++i)
	{
		mLines[i]->SetOffsetXY( mPosX, mPosY, mShowWidth, mShowHeight, mRealScale );
	}
}

/* virtual */ bool SymbolPanel::MouseButton( int btn, bool up )
{
	CheckControlLines();
	bool res = false;

	if ( btn == wxMOUSE_BTN_LEFT )
	{
		if (up)
		{
			EndDragLine();
		}
		else
		{
			res = BeginDragLine();
		}
	}

	if ( !res )
	{
		res = EditPanel::MouseButton(btn, up);
	}

	return res;
}

/* virtual */ bool SymbolPanel::MouseModifiersButton( int modifier, int btn, bool up )
{
	if (EditPanel::MouseModifiersButton(modifier, btn, up))
	{
		return true;
	}
	return false;
}

/* virtual */ bool SymbolPanel::MouseMoving( int modifier, int btn )
{
	if ( !mDragLine &&  EditPanel::MouseMoving(modifier, btn) )
	{
		return true;
	}

	if ( DragLine() )
	{
		return true;
	}
	return CheckControlLines();
}



bool SymbolPanel::CheckControlLines()
{
	bool res = false;
	if ( !mDragLine && !mDrawing )
	{
		mActiveLine = -1;
		for (int i = 0; i < clNum; ++i)
		{
			if ( mLines[i]->CheckMouse() )
			{
				mActiveLine = i;
				this->SetCursor( mLines[i]->GetCursor() );
				this->SetToolTip( mLines[i]->GetToolTip() );
			}
		}
		if ( mActiveLine == -1 )
		{
			this->SetToolTip( "" );
			this->SetCursor( wxNullCursor );
			mDrawCursor = true;
		}
		else
		{
			mDrawCursor = false;
			res = true;
			PaintNow();
		}
	}
	return res;
}



bool SymbolPanel::BeginDragLine()
{
	mDragLine = mActiveLine != -1 && !mDrawing;
	return mDragLine;
}



bool SymbolPanel::DragLine()
{
	if (mDragLine && mActiveLine != -1)
	{
		if (mMousePoint.x != -1 && mMousePoint.y != -1 && mMousePoint != mDragPoint )
		{
			mLines[mActiveLine]->SetValue( mMousePoint );
			SyncronizeValues();
			mDragPoint = mMousePoint;
			PaintNow();
			return true;
		}
	}
	return false;
}



void SymbolPanel::EndDragLine()
{
	mDragLine = false;
	mDrawCursor = true;
	mActiveLine = -1;
}



void SymbolPanel::SyncronizeValues()
{
	SymbolInfoPtr sym = mFontInfo->GetSymbol( mSymbolNumber );
	sym->SetWidth( mLines[clSymbolWidth]->GetValue() );
	sym->SetHeight( mLines[clSymbolHeight]->GetValue() );
	mFontInfo->SetBaseLine( mLines[clBaseLine]->GetValue() );
	mFontInfo->SetCapLine( mLines[clCapLine]->GetValue() );
	mFontInfo->SetLowLine( mLines[clLowLine]->GetValue() );
}


