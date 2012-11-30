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
		mPalettes[i]->Initiate( Palette::bppMono, (wxByte*) NULL );
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

	this->SetSpinsBase();
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
	mOwnerType->Enable( !b );
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



void PaletteWindowImpl::ChangeOwnerToCurrentPage( wxWindowID id )
{
	for (size_t i = 0; i < PalOwners::poNum; ++i)
	{
		if (PalOwners::OwnerID[i] == id)
		{
			mOwnerType->SetSelection(i);
			OwnerChanged();
			break;
		}
	}
}



/* virtual */ void PaletteWindowImpl::OnCommandEvent( wxCommandEvent& event )
{
	switch( event.GetId() )
	{
		case wxID_OWNER_CHOICE:
			OwnerChanged();
		break;

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
	int owner = -1;
	bool ownerToRecalc = false;

	switch( event.GetId() )
	{
		case wxID_ANY:
			ownerToRecalc = true;
			owner = mOwnerType->GetSelection();
		break;

		case wxID_FONTEDITOR:
			owner = PalOwners::poFontEditor;
		break;

		case wxID_IMAGEEDITOR:
			owner = PalOwners::poImageEditor;
		break;
	}

	if (owner >= 0 && CheckLocked() )
	{

		Palette* oldPal = mPalettes[owner];
		mPalettes[owner] = event.GetPalette()->Clone();
		mOwnerType->SetSelection( owner );
		OwnerChanged();
		delete oldPal;
		this->Lock( event.GetLock() );

		if ( ownerToRecalc )
		{
			EditorRebuildDataEvent* rebuildEvent = new EditorRebuildDataEvent( 
											PalOwners::OwnerID[owner], 
											EditorRebuildDataEvent::whPaletteChanged,
											mPalettes[owner] );
			wxTheApp->QueueEvent( rebuildEvent );
		}
	}
	event.Skip();
}