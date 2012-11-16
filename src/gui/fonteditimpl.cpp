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
#include "panels/symbolpanel.h"
#include "symboleditgui.h"
#include "fonteditimpl.h"
#include "fontsettingsimpl.h"

FontEditor::FontEditor(  wxWindow* parent ):
	FontEditGui( parent ),
	mSymbolEditor( new SymbolEditGui( mFontScrolledBack ) ),
	mCurrentFont( NULL ),
	mCurrentSymbol( 0 ),
	mHasChanges( false )
{
	mSymbolEditor->GetSymbolPanel()->SetAlign( utdHCenter | utdVCenter | utdExpand);
	mCentralSizer->Add( mSymbolEditor, 1, wxEXPAND, 5 );
	this->Layout();
	wxTheApp->Bind( uttEVT_CHANGEFONT, &FontEditor::OnFontChangeEvent, this );
	wxTheApp->Bind( uttEVT_SYMBOLSELECT, &FontEditor::OnSymbolSelection, this );
}



FontEditor::~FontEditor(void)
{
	wxTheApp->Unbind( uttEVT_CHANGEFONT, &FontEditor::OnFontChangeEvent, this );
	wxTheApp->Unbind( uttEVT_SYMBOLSELECT, &FontEditor::OnSymbolSelection, this );
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



void FontEditor::Render(wxDC& dc)
{
}



void FontEditor::UpdateFont()
{
	if (!mCurrentFont)
	{
		return;
	}
	UpdateRibbon();
}



void FontEditor::UpdateRibbon()
{
	Symbols& sym = mCurrentFont->GetSymbols();
	mSymbolsRibbon->Reserve( sym.size() );
	int w =  mCurrentFont->GetMaxWidth();
	int h =  mCurrentFont->GetMaxHeight();
	for ( size_t i = 0; i < sym.size(); ++i )
	{
		SymbolInfo& symbol = sym[i];
		wxBitmap* bmp = Helpers::CreateBitmap( (Pixel*) symbol.GetData(),w, h );
		mSymbolsRibbon->SetBitmap( i, bmp );
	}

	mSymbolsRibbon->RefillHolder();
	this->Layout();
}



/* virtual */ void FontEditor::OnPaint(wxPaintEvent& event)
{
	event.Skip();
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
	mCurrentSymbol = event.GetKey();
	mSymbolEditor->GetSymbolPanel()->SetFontInfo( mCurrentFont, mCurrentSymbol );
	event.Skip();
}