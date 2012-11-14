/***************************************************************
 * Name:      fonteditimpl.cpp
 * Purpose:   Code for FontEditor Class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-01-17
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"

#include "fontinfo.h"
#include "symbolpanel.h"
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
	mCentralSizer->Add( mSymbolEditor, 1, wxEXPAND, 5 );
	this->Layout();
	wxTheApp->Bind( uttEVT_CHANGEFONT, &FontEditor::OnFontChangeEvent, this );
}



FontEditor::~FontEditor(void)
{
	delete mCurrentFont;
}



/* virtual */ void FontEditor::OnFontChangeEvent( ChangeFontEvent& event )
{
	this->SetFont( event.GetFontInfo() );
	event.Skip();
}



SymbolPanel* FontEditor::GetSymbolPanel()
{
    return mSymbolEditor->GetSymbolPanel();
}



void FontEditor::SetFont( FontInfo* newFont )
{
	if (!mCurrentFont )
	{
		if (!CheckChanges())
		{
			return;
		}
		delete mCurrentFont;
	}

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

	for ( size_t i = 0; i < sym.size(); ++i )
	{
		SymbolInfo& symbol = sym[i];
		wxBitmap* bmp = DrawPanel::CreateBitmap( (Pixel*) symbol.GetData(), symbol.mWidth, symbol.mHeight );
		mSymbolsRibbon->SetBitmap( i, bmp );
	}

	mSymbolsRibbon->RefillHolder();
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

