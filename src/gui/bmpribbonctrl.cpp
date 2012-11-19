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



BitmapRibbonCtrl::BitmapRibbonCtrl(  wxWindow* parent ):
	BitmapRibbonGui( parent ),
	mThumbnails( new ThumbnailsArray( 0 ) ),
	mCurrent( 0 ),
	mToShow( 6 )
{
	this->Bind( wxEVT_SIZE, &BitmapRibbonCtrl::OnSize, this );
}



BitmapRibbonCtrl::~BitmapRibbonCtrl(void)
{
	this->Unbind( wxEVT_SIZE, &BitmapRibbonCtrl::OnSize, this );
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
	for ( size_t i = 0; i < mThumbnails->GetCount(); ++i )
	{
		if (i >= from && i < to)
		{
			mThumbnails->Item(i)->Enable();
			mThumbnails->Item(i)->Show();
			mBitmapsHolder->Add( mThumbnails->Item(i), 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5  );
		}
		else
		{
			mThumbnails->Item(i)->Hide();
			mThumbnails->Item(i)->Disable();
		}
	}
	this->Layout();
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



/* virtual */ void BitmapRibbonCtrl::OnButtonClick( wxCommandEvent& event )
{ 
	int inc = 1;
	switch ( event.GetId() )
	{
		case wxID_SCROLLLEFT_BTN:
			inc = -1;
		case wxID_SCROLLRIGHT_BTN:
			DoIncrement( inc );
		break;

		default:
			wxLogMessage( wxString::Format("BitmapRibbonCtrl::OnButtonClick: Unknown button id: %d", event.GetId()) );
		break;
	}
	event.Skip(); 
}



/* virtual */ void BitmapRibbonCtrl::OnSize( wxSizeEvent& event )
{
	CalculateThumbsCount( true, event.GetSize() );
	RefillHolder( false );
	event.Skip();
}