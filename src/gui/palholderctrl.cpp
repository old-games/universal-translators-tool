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



PaletteHolderCtrl::PaletteHolderCtrl(  wxWindow* parent ):
	PaletteHolderGui( parent )
	//mPaletteCtrl(new PaletteWindowImpl( parent ))
{
	mPaletteCtrl = new PaletteWindowImpl( this );
	mPaletteCtrl->Hide();
//	mPalHolderSizer->Add( mPaletteCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

}



PaletteHolderCtrl::~PaletteHolderCtrl(void)
{
}



void PaletteHolderCtrl::UpdateState()
{
	wxSize size = this->GetClientSize();

	if (mPaletteCtrl->IsShown())
	{
		mPalHolderSizer->Add( mPaletteCtrl, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
		size += mPaletteCtrl->GetMinSize();
	}
	else
	{
		mPalHolderSizer->Detach( (wxWindow*) mPaletteCtrl  );
		size -= mPaletteCtrl->GetMinSize();
	}

	this->SetSize(size);
	this->Layout();
	//	wxSize size = mPaletteCtrl->IsShown() ? mPalHolderSizer->GetSize() : mPalHideBtn->GetSize();
	//	this->SetSize(size);
}



/* virtual */ void PaletteHolderCtrl::OnPalHideBtnClick( wxCommandEvent& event )
{
	mPaletteCtrl->Show( !mPaletteCtrl->IsShown() );
	UpdateState();
	event.Skip();
}