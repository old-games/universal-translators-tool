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
	mPalPanel( NULL ),
	mPalette( NULL )
{
	mPalPanel = new PalettePanel( this, mPalette, true );
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

	//PalTypeChanged();
	//mPalScrolledBack->Bind( wxEVT_PAINT, &PaletteWindowImpl::OnPaint, this );
	//wxTheApp->Bind( uttEVT_CHANGEPALETTE, &PaletteWindowImpl::OnPaletteChangeEvent, this );

	this->SetSpinsBase();
}



PaletteWindowImpl::~PaletteWindowImpl(void)
{
	this->Unbind( wxEVT_PAINT, &PaletteWindowImpl::OnPaint, this );
	wxTheApp->Unbind( uttEVT_CHANGEPALETTE, &PaletteWindowImpl::OnPaletteChangeEvent, this );
}



void PaletteWindowImpl::OnPaint( wxPaintEvent& event )
{
	UpdateSpins();
	event.Skip();
}



void PaletteWindowImpl::PalTypeChanged()
{
	bool changeCGA = mPalType->GetSelection() == Palette::bpp2;

	if ( changeCGA )
	{
		mPalette->SetCGAType( mCGAType->GetSelection(), mCGAIntensity->IsChecked() );
	}
	else
	{
		mPalette->ChangeBPP( (Palette::BPP) mPalType->GetSelection() );
	}

	mPalPanel->SetCurrentPalette( mPalette );


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

	mLISpin->Enable( mPalPanel->GetCurrentPalette()->IsIndexed() );
	mRISpin->Enable( mLISpin->IsEnabled() );

	if ( mLISpin->IsEnabled() )
	{
		int i = Palette::ColourNumber[ mPalType->GetSelection() ];
		mLISpin->SetRange(0, i - 1);
		mRISpin->SetRange(0, i - 1);
	}
}



void PaletteWindowImpl::LockChanged()
{
	bool b = IsLocked();
	SpinEnable( !b );
	mPalType->Enable( !b );
}



void PaletteWindowImpl::Lock( bool b /* true */ )
{
	mLockCheck->SetValue( b );
	LockChanged();
}



UttColour PaletteWindowImpl::GetColour(bool right)
{
	wxSpinCtrl* r = right ? mRRSpin : mLRSpin;
	wxSpinCtrl* g = right ? mRGSpin : mLGSpin;
	wxSpinCtrl* b = right ? mRBSpin : mLBSpin;
	int ind = -1;
	if (mPalPanel->GetCurrentPalette()->IsIndexed())
	{
		wxSpinCtrl* i = right ? mRISpin : mLISpin;
		ind = i->GetValue();
	}
	return UttColour( wxColour(r->GetValue(), g->GetValue(), b->GetValue()), ind );
}



void PaletteWindowImpl::SetColour(bool right, const UttColour& colour)
{
	//if (IsLocked())
	//{
	//	wxLogMessage("Palette is locked to modify!");
	//	return;
	//}

	wxSpinCtrl* r = right ? mRRSpin : mLRSpin;
	wxSpinCtrl* g = right ? mRGSpin : mLGSpin;
	wxSpinCtrl* b = right ? mRBSpin : mLBSpin;
	wxSpinCtrl* i = right ? mRISpin : mLISpin;

	r->SetValue( colour.Red() );
	g->SetValue( colour.Green() );
	b->SetValue( colour.Blue() );
	if (colour.GetIndex() >= 0)
	{
		i->SetValue( colour.GetIndex() );
	}

	UpdateColour( right );
}


void PaletteWindowImpl::SetSpinsBase()
{
	int base = mHexCheck->IsChecked() ? 16 : 10;
	mRRSpin->SetBase( base );
	mLRSpin->SetBase( base );
	mRGSpin->SetBase( base ); 
	mLGSpin->SetBase( base );
	mRBSpin->SetBase( base );
	mLBSpin->SetBase( base );
	mLISpin->SetBase( base );
	mRISpin->SetBase( base );
	this->Update();
}



int	PaletteWindowImpl::FindColour( bool right, const UttColour& colour, bool andSet /* false */)
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
	UttColour colour = GetColour(right);
	mPalPanel->SetColour( right, colour );
}



void PaletteWindowImpl::IndexChanged(bool right)
{
	wxSpinCtrl* spin = right ? mRISpin : mLISpin;
	wxPoint pos = mPalPanel->GetCurrentPalette()->GetIndexCoordinates( spin->GetValue() );
	mPalPanel->SetColourPosition(pos, right);
}



void PaletteWindowImpl::UpdateSpin(bool right)
{
	SetColour( right, mPalPanel->GetColour(right) );
}



bool PaletteWindowImpl::CheckLocked()
{
	if (IsLocked())
	{
		if (YESNODIALOG("Change palette anyway?", "Palette is locked!")	!= wxID_YES)
		{
			return false;
		}
	}
	return true;
}



/* virtual */ void PaletteWindowImpl::OnCommandEvent( wxCommandEvent& event )
{
	switch( event.GetId() )
	{
		case wxID_PALLOCK_CHECK:
			LockChanged();
		break;

		case wxID_HEX_CHECK:
			SetSpinsBase();
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

		case wxID_RI_SPIN:
			IndexChanged( true );
		break;

		case wxID_LI_SPIN:
			IndexChanged( false );
		break;


		default:
			wxLogError( wxString::Format( "PaletteWindow: unknown spin id %d", event.GetId() ) );
	}
}



/* virtual */ void PaletteWindowImpl::OnPaletteChangeEvent( ChangePaletteEvent& event )
{
	if (CheckLocked() )
	{

		Palette* oldPal = mPalette;
		mPalette = event.GetPalette()->Clone();
		delete oldPal;
		this->Lock( event.GetLock() );

		//if ( ownerToRecalc )
		//{
		//	EditorRebuildDataEvent* rebuildEvent = new EditorRebuildDataEvent( 
		//									PalOwners::OwnerID[owner], 
		//									EditorRebuildDataEvent::whPaletteChanged,
		//									mPalettes[owner] );
		//	wxTheApp->QueueEvent( rebuildEvent );
		//}
	}
	event.Skip();
}