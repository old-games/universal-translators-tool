/***************************************************************
 * Name:      palholderctrl.cpp
 * Purpose:   Implementation of PaletteHolderCtrl
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-19
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "palholderctrl.h"
#include "palwindowimpl.h"



PaletteHolderCtrl::PaletteHolderCtrl( wxWindow* parent, wxWindowID eventsId, wxWindow* grand, wxFlexGridSizer* parentSizer ):
	PaletteHolderGui( parent ),
	mPaletteCtrl(new PaletteWindowImpl( this, eventsId )),
	mGrand( grand ),
	mParentSizer( parentSizer )
{
	mPaletteCtrl->Hide();
	mPalHolderSizer->Add( mPaletteCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
}



PaletteHolderCtrl::~PaletteHolderCtrl(void)
{
}



void PaletteHolderCtrl::UpdateState()
{
	if (mPaletteCtrl->IsShown())
	{
		mParentSizer->AddGrowableRow(2);
	}
	else
	{
		mParentSizer->RemoveGrowableRow(2);
	}

	mGrand->Layout();
}



/* virtual */ void PaletteHolderCtrl::OnPalHideBtnClick( wxCommandEvent& event )
{
	mPaletteCtrl->Show( !mPaletteCtrl->IsShown() );
	UpdateState();
	event.Skip();
}