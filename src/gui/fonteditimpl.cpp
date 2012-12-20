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
#include "types/ieditor.h"
#include "panels/symbolpanel.h"
#include "symboleditgui.h"
#include "fonteditimpl.h"
#include "fontsettingsimpl.h"



const wxString	UUT_FONT_EXTENSIONS = "UTT Font files (*.uft)|*.uft";



FontEditor::FontEditor(  wxWindow* parent ):
	FontEditGui( parent ),
	IEditor( this, etFont, "Font editor" ),
	mSymbolEditor( new SymbolEditGui( mSymEditorOwner ) ), 
	mCurrentFont( NULL ),
	mCurrentSymbol( 0 ),
	mHasChanges( false )
{
	mSymbolEditor->GetSymbolPanel()->SetAlign( utdHCenter | utdVCenter | utdExpand);
	mSymbolEditor->Disable();
	mCentralSizer->Add( mSymbolEditor, 1, wxEXPAND, 5 );
	this->Layout();
	wxTheApp->Bind( uttEVT_CHANGEFONT, &FontEditor::OnFontChangeEvent, this, this->GetId() );
	wxTheApp->Bind( uttEVT_SYMBOLSELECT, &FontEditor::OnSymbolSelection, this, mSymbolsRibbon->GetId() );
	wxTheApp->Bind( uttEVT_REBUILDDATA, &FontEditor::OnRebuildDataEvent, this, this->GetId() );
}



FontEditor::~FontEditor(void)
{
	wxTheApp->Unbind( uttEVT_CHANGEFONT, &FontEditor::OnFontChangeEvent, this, this->GetId() );
	wxTheApp->Unbind( uttEVT_SYMBOLSELECT, &FontEditor::OnSymbolSelection, this, mSymbolsRibbon->GetId() );
	wxTheApp->Unbind( uttEVT_REBUILDDATA, &FontEditor::OnRebuildDataEvent, this, this->GetId() );
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
	mSymbolEditor->Disable();
}



void FontEditor::SetFont( FontInfo* newFont )
{
	ClearFont();
	mCurrentFont = newFont->Clone();
	SetPaletteAsMain();
	UpdateFont();
	mSymbolEditor->Enable();
}



bool FontEditor::CheckChanges()
{
	if (mHasChanges)
	{
		int res = wxMessageDialog(this, "Save changes?", "Font has changes", wxYES_NO | wxCANCEL | wxCENTRE | wxCANCEL_DEFAULT).ShowModal();

		if (res == wxID_OK)
		{
			mHasChanges = !SaveFont();
		}
		else
		{
			mHasChanges = false;
		}

	}
	return !mHasChanges;
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
	mSymbolsRibbon->Reserve( sym.size() );
	for ( size_t i = 0; i < sym.size(); ++i )
	{
		wxBitmap* bmp =  sym[i].GetData()->GetBitmap( mCurrentFont->GetPalette() ); 
		mSymbolsRibbon->SetBitmap( i, bmp );
	}

	mSymbolsRibbon->RefillHolder();
	this->Update();
}



void FontEditor::CurrentSymbolChanged()
{
	mHasChanges = true;

	if (mCurrentFont && mCurrentSymbol < mCurrentFont->GetSymbols().size() )
	{
		SymbolInfo& info = mCurrentFont->GetSymbols()[mCurrentSymbol];
		if (info.IsOk())
		{
			info.SetData( mSymbolEditor->GetIndexMask() );
			wxBitmap* bmp = info.GetData()->GetBitmap( mCurrentFont->GetPalette() ); 
			mSymbolsRibbon->UpdateBitmap( mCurrentSymbol, bmp );
		}
	}
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
		ChangePaletteEvent palEvent( mSymbolEditor->GetPaletteCtrlId(), pal, true );
		wxTheApp->QueueEvent( palEvent.Clone() );
	}
}



/* virtual */ bool FontEditor::SaveEditor( wxOutputStream& output )
{
	return mCurrentFont ? mCurrentFont->SaveToStream(output) : false;
}



/* virtual */ bool FontEditor::LoadEditor( wxInputStream& input )
{
	FontInfo* fontInfo = new FontInfo();
	bool res = fontInfo->LoadFromStream( input );

	if ( res )
	{
		SetFont( fontInfo );

	}

	delete fontInfo;

	return res;
}



bool FontEditor::SaveFont()
{

	if (!mCurrentFont )
	{
		wxLogWarning("Font is not ready to save!");
	}
	else
	{
		wxFileDialog dlg( this, "Save font as...", wxEmptyString, "fontfile", UUT_FONT_EXTENSIONS, wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
		if (dlg.ShowModal() == wxID_OK)
		{
			mHasChanges = mCurrentFont->SaveToFile( dlg.GetPath() );
		}
	}
	return !mHasChanges;
}



void FontEditor::LoadFont()
{
	wxFileDialog dlg( this, "Open UTT font...", wxEmptyString, "fontfile", UUT_FONT_EXTENSIONS, wxFD_OPEN|wxFD_FILE_MUST_EXIST );
	if (dlg.ShowModal() == wxID_OK)
	{
		FontInfo* fontInfo = new FontInfo();
		if ( fontInfo->LoadFromFile( dlg.GetPath() ) )
		{
			SetFont( fontInfo );
		}
		delete fontInfo;
	}
}



/* virtual */ void FontEditor::OnBtnClick( wxCommandEvent& event )
{
	switch (event.GetId())
	{

		case wxID_SAVE_BTN:
			SaveFont();
		break;

		case wxID_LOAD_BTN:
			LoadFont();
		break;

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

		case EditorRebuildDataEvent::whIndexMaskChanged:
			CurrentSymbolChanged();
		break;

		default:
			wxLogError("FontEditor::OnRebuildDataEvent error: unknown \"what to do\" id (%d)", event.GetWhat());
		break;
	}
	event.Skip();
}