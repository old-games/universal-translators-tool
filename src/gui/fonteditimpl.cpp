/***************************************************************
 * Name:      fonteditimpl.cpp
 * Purpose:   Code for FontEditor Class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-01-17
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"

#include "types/fontinfo.h"
#include "types/indexmask.h"
#include "types/palette.h"
#include "panels/symbolpanel.h"
#include "symboleditgui.h"
#include "fonteditimpl.h"
#include "fontsettingsimpl.h"

FontEditor::FontEditor(  wxWindow* parent ):
	FontEditGui( parent ),
	mSymbolEditor( new SymbolEditGui( mSymEditorOwner ) ), //mFontScrolledBack ) ),
	mCurrentFont( NULL ),
	mCurrentSymbol( 0 ),
	mHasChanges( false )
{
	mSymbolEditor->GetSymbolPanel()->SetAlign( utdHCenter | utdVCenter | utdExpand);
	mCentralSizer->Add( mSymbolEditor, 1, wxEXPAND, 5 );
	this->Layout();
	wxTheApp->Bind( uttEVT_CHANGEFONT, &FontEditor::OnFontChangeEvent, this );
	wxTheApp->Bind( uttEVT_SYMBOLSELECT, &FontEditor::OnSymbolSelection, this );
	wxTheApp->Bind( uttEVT_REBUILDDATA, &FontEditor::OnRebuildDataEvent, this, wxID_FONTEDITOR );
}



FontEditor::~FontEditor(void)
{
	wxTheApp->Unbind( uttEVT_CHANGEFONT, &FontEditor::OnFontChangeEvent, this );
	wxTheApp->Unbind( uttEVT_SYMBOLSELECT, &FontEditor::OnSymbolSelection, this );
	wxTheApp->Unbind( uttEVT_REBUILDDATA, &FontEditor::OnRebuildDataEvent, this, wxID_FONTEDITOR );
	ClearFont( true );
}



SymbolPanel* FontEditor::GetSymbolPanel()
{
    return mSymbolEditor->GetSymbolPanel();
}



void FontEditor::ClearFont( bool force /* false */ )
{
	if (mCurrentFont != NULL)
	{
		if (!CheckChanges() && !force)
		{
			return;
		}
		delete mCurrentFont;
		mCurrentFont = NULL;
	}
}



void FontEditor::SetFont( FontInfo* newFont )
{
	ClearFont();
	mCurrentFont = newFont->Clone();
	SetPaletteAsMain();
	UpdateFont();
}



bool FontEditor::CheckChanges()
{
	if (!mHasChanges)
	{
		return true;
	}

	int res = wxMessageDialog(this, "Save changes?", "Font has changes", wxYES_NO | wxCANCEL | wxCENTRE | wxCANCEL_DEFAULT).ShowModal();

	if (res == wxID_OK)
	{
		return SaveFont();
	}

	mHasChanges = false;
	return true;
}



bool FontEditor::SaveFont()
{
	return true;
}



bool FontEditor::CreateFont()
{
	if ( mCurrentFont != NULL && !CheckChanges() )
	{
		return false;
	}

	mCurrentFont = new FontInfo();
	if ( ShowSettings() )
	{
		mCurrentSymbol = 0;
		mSymbolEditor->GetSymbolPanel()->SetFontInfo( mCurrentFont, mCurrentSymbol );
		return true;
	}
	return false;
}



bool FontEditor::ShowSettings()
{
	if (mCurrentFont == NULL)
	{
		return CreateFont();
	}

	FontSettingsImpl settings( this, mCurrentFont );
	return settings.ShowModal() != wxID_CANCEL;
}



void FontEditor::UpdateFont()
{
	if (!mCurrentFont)
	{
		return;
	}
	UpdateRibbon();
	SetCurrentSymbol( mCurrentSymbol );
}



void FontEditor::SetCurrentSymbol(int n)
{
	mSymbolsRibbon->ActiveChanged( mCurrentSymbol, n );
	mCurrentSymbol = n;
	mSymbolEditor->GetSymbolPanel()->SetFontInfo( mCurrentFont, mCurrentSymbol );
}



void FontEditor::UpdateRibbon()
{
	Symbols& sym = mCurrentFont->GetSymbols();
	mSymbolsRibbon->Clear();

	for ( size_t i = 0; i < sym.size(); ++i )
	{
		wxBitmap* bmp =  sym[i].GetData()->GetBitmap( mCurrentFont->GetPalette() ); 
		mSymbolsRibbon->SetBitmap( i, bmp );
	}

	mSymbolsRibbon->RefillHolder();
	this->Update();
}



void FontEditor::ChangeFontPalette( Palette* pal )
{
	mCurrentFont->SetPalette( pal );
	UpdateFont();
}



void FontEditor::SetPaletteAsMain()
{
	Palette* pal = mCurrentFont->GetPalette();
	if ( pal && pal->IsOk() )
	{
		ChangePaletteEvent palEvent( wxID_FONTEDITOR, pal, true );
		wxTheApp->QueueEvent( palEvent.Clone() );
	}
}



/* virtual */ void FontEditor::OnBtnClick( wxCommandEvent& event )
{
	switch (event.GetId())
	{
		case wxID_CREATE_FONT:
			CreateFont();
		break;

		case wxID_FONT_SETTINGS:
			ShowSettings();
		break;

		default:
			wxLogError("FontEditor::OnBtnClick error: unknown event id");
	}
	event.Skip();
}



/* virtual */ void FontEditor::OnFontChangeEvent( ChangeFontEvent& event )
{
	this->SetFont( event.GetFontInfo() );
	event.Skip();
}



/* virtual */ void FontEditor::OnSymbolSelection( SymbolSelectionEvent& event )
{
	SetCurrentSymbol( event.GetKey() );
	event.Skip();
}



/* virtual */ void FontEditor::OnRebuildDataEvent( EditorRebuildDataEvent& event )
{
	switch (event.GetWhat())
	{
		case EditorRebuildDataEvent::whPaletteChanged:
			ChangeFontPalette( event.GetPalette() );
		break;

		default:
			wxLogError("FontEditor::OnRebuildDataEvent error: unknown \"what to do\" id (%d)", event.GetWhat());
		break;
	}
	event.Skip();
}