/***************************************************************
 * Name:      bmpribbonctrl.cpp
 * Purpose:   
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "panels/thumbnail.h"
#include "bmpribbonctrl.h"

#define RIBBON_BUTTON_PAUSE 50

BitmapRibbonCtrl::BitmapRibbonCtrl(  wxWindow* parent ):
	BitmapRibbonGui( parent ),
	mThumbnails( new ThumbnailsArray( 0 ) ),
	mCurrent( 0 ),
	mToShow( 6 ),
	mBtnPressed( wxID_ANY ),
	mButtonTimer( this )
{
	this->Bind( wxEVT_SIZE, &BitmapRibbonCtrl::OnSize, this );
	this->Bind( wxEVT_TIMER, &BitmapRibbonCtrl::OnTimer, this );
}



BitmapRibbonCtrl::~BitmapRibbonCtrl(void)
{
	mButtonTimer.Stop();
	this->Unbind( wxEVT_SIZE, &BitmapRibbonCtrl::OnSize, this );
	this->Unbind( wxEVT_TIMER, &BitmapRibbonCtrl::OnTimer, this );
	Clear();
	delete mThumbnails;
}



void BitmapRibbonCtrl::Clear()
{
	WX_CLEAR_ARRAY( *mThumbnails );
	mThumbnails->Clear();
}



void BitmapRibbonCtrl::RefillHolder( bool recalcCount /* true */)
{
	if (recalcCount)
	{
		CalculateThumbsCount();
	}

	mBitmapsHolder->Clear();

	if (mThumbnails->GetCount() == 0)
	{
		mBitmapsHolder->Add( 0, 0, 1, wxEXPAND, 5 );
		this->Layout();
		return;
	}

	size_t _max = mThumbnails->GetCount() - mToShow;
	if ( mCurrent > _max )
	{
		mCurrent = _max;
	}

	size_t from = mCurrent;
	size_t to = mCurrent + mToShow;
	size_t i = 0;

	for ( ThumbnailsArray::iterator it = mThumbnails->begin(); it != mThumbnails->end(); ++it )
	{
		if (i >= from && i < to)
		{
			(*it)->Enable();
			(*it)->Show();
			mBitmapsHolder->Add( *it, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5  );
		}
		else
		{
			(*it)->Hide();
			(*it)->Disable();
		}
		++i;
	}
	this->Layout();
}



void BitmapRibbonCtrl::UpdateBitmap( size_t n, wxBitmap* bmp )
{
	if (n < mThumbnails->GetCount())
	{
		mThumbnails->Item(n)->SetBitmap(bmp);
	}
}



void BitmapRibbonCtrl::Reserve( size_t n )
{
	mThumbnails->reserve( n );
}


void BitmapRibbonCtrl::SetBitmap( size_t n, wxBitmap* bmp )
{
	ThumbnailPanel* dp = new ThumbnailPanel(n, this);
	dp->SetAlign( utdHCenter | utdVCenter | utdExpand);
	dp->SetDrawFocus( true );
	dp->SetBitmap( bmp );

	mThumbnails->Insert( dp, n );
}



void BitmapRibbonCtrl::DoIncrement( int step )
{
	if (mCurrent + step < mThumbnails->GetCount() )
	{
		mCurrent += step;
		RefillHolder();
	}
}



void BitmapRibbonCtrl::CalculateThumbsCount( bool useSize /* false */, const wxSize& size /* wxDefaultSize */)
{
	mToShow = 0;
	wxSize boxSize = useSize ? size : mBitmapsHolder->GetSize();

	if (mThumbnails->GetCount() == 0)
	{
		return;
	}

	mToShow = boxSize.x / (boxSize.y + 5);

	if (mToShow == 0)
	{
		mToShow = 1;
	}

	if (mToShow > mThumbnails->GetCount())
	{
		mToShow = mThumbnails->GetCount();
	}

}



void BitmapRibbonCtrl::ActiveChanged( int old, int n )
{
	wxASSERT( (size_t) old < mThumbnails->GetCount() && (size_t) n < mThumbnails->GetCount() );
	mThumbnails->Item(old)->SetActive(false);
	mThumbnails->Item(n)->SetActive();

	mThumbnails->Item(old)->Refresh();
	mThumbnails->Item(n)->Refresh();
}



bool BitmapRibbonCtrl::CheckMouseInButton()
{
	wxButton* btn = NULL;
	switch ( mBtnPressed )
	{
		case wxID_SCROLLLEFT_BTN:
			btn = mScrollLeftBtn;
		break;

		case wxID_SCROLLRIGHT_BTN:
			btn = mScrollRightBtn;
		break;
	}

	return btn != NULL && btn->IsMouseInWindow();
}


/* virtual */ void BitmapRibbonCtrl::OnButtonClick( wxCommandEvent& event )
{
	event.Skip();
}



/* virtual */ void BitmapRibbonCtrl::OnMouseDown( wxMouseEvent& event )
{ 
	mBtnPressed = event.GetId();
	mButtonTimer.Start( RIBBON_BUTTON_PAUSE );
	event.Skip(); 
}



/* virtual */ void BitmapRibbonCtrl::OnMouseUp( wxMouseEvent& event )
{ 
	mBtnPressed = wxID_ANY;
	mButtonTimer.Stop();
	event.Skip(); 
}



/* virtual */ void BitmapRibbonCtrl::OnSize( wxSizeEvent& event )
{
	CalculateThumbsCount( true, event.GetSize() );
	RefillHolder( false );
	event.Skip();
}



/* virtual */ void BitmapRibbonCtrl::OnTimer( wxTimerEvent& event )
{
	wxMouseState state = wxGetMouseState();
	
	if ( !state.LeftIsDown() || !CheckMouseInButton() )
	{
		mBtnPressed = wxID_ANY;
	}

	int inc = 1;
	switch ( mBtnPressed )
	{
		case wxID_SCROLLLEFT_BTN:
			inc = -1;
		case wxID_SCROLLRIGHT_BTN:
			DoIncrement( inc );
		break;

		default:
			//wxLogMessage( wxString::Format("BitmapRibbonCtrl::OnButtonClick: Unknown button id: %d", event.GetId()) );
			mBtnPressed = wxID_ANY;
			mButtonTimer.Stop();
		break;
	}
	event.Skip();
}


#undef RIBBON_BUTTON_PAUSE