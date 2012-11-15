/***************************************************************
 * Name:      palwindowimpl.cpp
 * Purpose:   Code for PaletteWindowImpl class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-07
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"

#include "panels/palettepanel.h"
#include "palwindowimpl.h"
#include "types/palette.h"



PaletteWindowImpl::PaletteWindowImpl(  wxWindow* parent ):
	PaletteWindowGui( parent ),
	mPalPanel( NULL )
{
	for (int i = 0; i < PalOwners::poNum; ++i)
	{
		mOwnerType->Append(PalOwners::OwnerName[i]);
		mPalettes[i] = new Palette();
		mPalettes[i]->Initiate( Palette::bppMono );
	}
	mOwnerType->SetSelection(0);

	mPalPanel = new PalettePanel( mPalScrolledBack, mPalettes[0], true );
	mPalHolder->Add( mPalPanel, 1, wxEXPAND, 5 );

	for (int i = 0; i < Palette::bppNum; ++i)
	{
		mPalType->Append(Palette::Names[i]);
	}
	mPalType->SetSelection(0);

	for (int i = 0; i < CGA_PALS_NUMBER; ++i)
	{
		mCGAType->Append( wxString::Format("CGA set #%d", i) );
	}
	mCGAType->SetSelection(0);

	PalTypeChanged();
	mPalScrolledBack->Bind( wxEVT_PAINT, &PaletteWindowImpl::OnPaint, this );
	wxTheApp->Bind( uttEVT_CHANGEPALETTE, &PaletteWindowImpl::OnPaletteChangeEvent, this );
}



PaletteWindowImpl::~PaletteWindowImpl(void)
{
	mPalScrolledBack->Unbind( wxEVT_PAINT, &PaletteWindowImpl::OnPaint, this );
	for (int i = 0; i < PalOwners::poNum; ++i)
	{
		delete mPalettes[i];
	}
}



void PaletteWindowImpl::OnPaint( wxPaintEvent& event )
{
	UpdateSpins();
	event.Skip();
}



void PaletteWindowImpl::OwnerChanged()
{
	int owner = mOwnerType->GetSelection();
	mPalType->SetSelection( mPalettes[owner]->GetPalType() );
	mCGAType->SetSelection( mPalettes[owner]->GetCGAType() );
	mCGAIntensity->SetValue( mPalettes[owner]->GetIntensity() );
	PalTypeChanged();
}



void PaletteWindowImpl::PalTypeChanged()
{
	int owner = mOwnerType->GetSelection();
	bool changeCGA = mPalType->GetSelection() == Palette::bpp2;

	if ( changeCGA )
	{
		mPalettes[owner]->SetCGAType( mCGAType->GetSelection(), mCGAIntensity->IsChecked() );
	}
	else
	{
		mPalettes[owner]->ChangeBPP( (Palette::BPP) mPalType->GetSelection() );
	}

	mPalPanel->SetCurrentPalette( mPalettes[owner] );

	bool cgaControls = mPalType->GetSelection() == Palette::bpp2;
	mCGAType->Enable( cgaControls );
	mCGAIntensity->Enable( cgaControls );
	SpinEnable( !cgaControls );
	mPalPanel->SetBitmapFromPalette();
	mPalPanel->Refresh();
	UpdateSpins();
}



void PaletteWindowImpl::SpinEnable(bool b /* true */)
{
	mRRSpin->Enable(b);
	mLRSpin->Enable(b);
	mRGSpin->Enable(b); 
	mLGSpin->Enable(b);
	mRBSpin->Enable(b);
	mLBSpin->Enable(b);
}



wxColour PaletteWindowImpl::GetColour(bool right)
{
	wxSpinCtrl* r = right ? mRRSpin : mLRSpin;
	wxSpinCtrl* g = right ? mRGSpin : mLGSpin;
	wxSpinCtrl* b = right ? mRBSpin : mLBSpin;
	return wxColour( r->GetValue(), g->GetValue(), b->GetValue() );
}



void PaletteWindowImpl::SetColour(bool right, const wxColour& colour)
{
	wxSpinCtrl* r = right ? mRRSpin : mLRSpin;
	wxSpinCtrl* g = right ? mRGSpin : mLGSpin;
	wxSpinCtrl* b = right ? mRBSpin : mLBSpin;
	r->SetValue( colour.Red() );
	g->SetValue( colour.Green() );
	b->SetValue( colour.Blue() );
	UpdateColour( right );
}



int	PaletteWindowImpl::FindColour( bool right, const wxColour& colour, bool andSet /* false */)
{
	int res = mPalPanel->FindColour( right, colour, andSet );
	if (res == -1)
	{
		wxLogMessage( wxString::Format("Colour %s not found in global palette", colour.GetAsString() ) );
	}
	return res;
}



void PaletteWindowImpl::UpdateColours()
{
	UpdateColour( false );
	UpdateColour( true );
}



void PaletteWindowImpl::UpdateSpins()
{
	UpdateSpin( false );
	UpdateSpin( true );
}



void PaletteWindowImpl::UpdateColour(bool right)
{
	wxColour colour = GetColour(right);
	mPalPanel->SetColour( right, colour );
}



void PaletteWindowImpl::UpdateSpin(bool right)
{
	SetColour( right, mPalPanel->GetColour(right) );
}



/* virtual */ void PaletteWindowImpl::OnCommandEvent( wxCommandEvent& event )
{
	switch( event.GetId() )
	{
		case wxID_OWNER_CHOICE:
			OwnerChanged();
		break;

		case wxID_CGA_CHOICE:
		case wxID_PAL_CHOICE:
		case wxID_INTENSITY_CHECK:
			PalTypeChanged();
		break;

		default:
			wxLogError( wxString::Format( "PaletteWindow: unknown command %d", event.GetId() ) );
	}
	event.Skip();
}



/* virtual */ void PaletteWindowImpl::OnSpinCtrl( wxSpinEvent& event )
{
	event.Skip();
	switch( event.GetId() )
	{
		case wxID_RR_SPIN:
		case wxID_RG_SPIN:
		case wxID_RB_SPIN:
			UpdateColour( true );
		break;

		case wxID_LR_SPIN:
		case wxID_LG_SPIN:
		case wxID_LB_SPIN:
			UpdateColour( false );
		break;

		default:
			wxLogError( wxString::Format( "PaletteWindow: unknown spin id %d", event.GetId() ) );
	}
}



/* virtual */ void PaletteWindowImpl::OnPaletteChangeEvent( ChangePaletteEvent& event )
{
	int owner = -1;
	switch( event.GetId() )
	{
		case wxID_FONTEDITOR:
			owner = PalOwners::poFontEditor;
		break;

		case wxID_IMAGEEDITOR:
			owner = PalOwners::poFontEditor;
		break;
	}

	if (owner >= 0)
	{
		Palette* oldPal = mPalettes[owner];
		mPalettes[owner] = event.GetPalette()->Clone();
		mOwnerType->SetSelection( owner );
		OwnerChanged();
		delete oldPal;
	}
	event.Skip();
}