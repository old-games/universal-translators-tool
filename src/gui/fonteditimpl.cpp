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
#include "types/symbolinfo.h"
#include "types/ieditor.h"
#include "panels/symbolpanel.h"
#include "symboleditgui.h"
#include "fonteditimpl.h"
#include "fontsettingsimpl.h"



const wxString	UTT_FONT_EXTENSIONS = "UTT Font files (*.uft)|*.uft";



FontEditor::FontEditor(  wxWindow* parent ):
	FontEditGui( parent ),
	IEditor( this, etFont, "Font editor" ),
	mSymbolEditor( NULL ), 
	mCurrentFont( NULL ),
	mCurrentSymbol( 0 )
{
	mSymbolEditor = new SymbolEditGui( mSymEditorOwner, this->GetId() );
	mSymbolEditor->GetSymbolPanel()->SetAlign( utdHCenter | utdVCenter | utdExpand);
	mSymbolEditor->Disable();
	mCentralSizer->Add( mSymbolEditor, 1, wxEXPAND, 5 );
	this->Layout();
//	wxTheApp->Bind( uttEVT_CHANGEFONT, &FontEditor::OnFontChangeEvent, this, this->GetId() );
	wxTheApp->Bind( uttEVT_SYMBOLSELECT, &FontEditor::OnSymbolSelection, this, mSymbolsRibbon->GetId() );
	wxTheApp->Bind( uttEVT_REBUILDDATA, &FontEditor::OnRebuildDataEvent, this, this->GetId() );
}



FontEditor::~FontEditor(void)
{
//	wxTheApp->Unbind( uttEVT_CHANGEFONT, &FontEditor::OnFontChangeEvent, this, this->GetId() );
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
	if (mCurrentFont)
	{
		if ( !force && CheckChanged())
		{
			return;
		}

		mCurrentFont = nullptr;
	}

	mSymbolEditor->Disable();
}



bool FontEditor::CreateFont()
{
	if ( mCurrentFont && !CheckChanged() )
	{
		return false;
	}

	mCurrentFont = std::make_shared<FontInfo>();

	if (ShowSettings())
	{
		mCurrentSymbol = 0;
		mSymbolEditor->GetSymbolPanel()->SetFontInfo( mCurrentFont, mCurrentSymbol );
		return true;
	}

	return false;
}



bool FontEditor::ShowSettings()
{
	if (!mCurrentFont)
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
		wxBitmap* bmp =  sym[i]->GetData()->GetBitmap( mCurrentFont->GetPalette() ); 
		mSymbolsRibbon->SetBitmap( i, bmp );
	}

	mSymbolsRibbon->RefillHolder();
	this->Update();
}



void FontEditor::CurrentSymbolChanged()
{
	Changed();

	if (mCurrentFont && mCurrentSymbol < mCurrentFont->GetSymbols().size() )
	{
		auto& symbols = mCurrentFont->GetSymbols();
		SymbolInfoPtr info = symbols[mCurrentSymbol];

		if (info->IsOk())
		{
			info->SetData( mSymbolEditor->GetIndexMask() );
			wxBitmap* bmp = info->GetData()->GetBitmap(mCurrentFont->GetPalette());
			mSymbolsRibbon->UpdateBitmap( mCurrentSymbol, bmp );
		}
	}
}



void FontEditor::ChangeFontPalette( PalettePtr pal )
{
	mCurrentFont->SetPalette( pal );
	UpdateFont();
}



void FontEditor::SetPaletteAsMain()
{
	PalettePtr pal = mCurrentFont->GetPalette();

	if ( pal && pal->IsOk() )
	{
		ChangePaletteEvent* palEvent = new ChangePaletteEvent ( this->GetId(), pal, false );
		wxTheApp->QueueEvent( palEvent );
	}
}



/* virtual */ bool FontEditor::SaveState( wxOutputStream& output )
{
	if (!mCurrentFont)
	{
		return false;
	}

	bool result = IEditor::SaveState(output) &&
		mCurrentFont->SaveToStream(output) && 
		this->SaveSimpleType<wxUint32>( output, mCurrentSymbol );

	if (result)
	{
		this->Changed( false );
	}

	return result;
}



/* virtual */ bool FontEditor::LoadState( wxInputStream& input, int version )
{
	FontInfoPtr fontInfo = std::make_shared<FontInfo>();

	bool res = IEditor::LoadState(input, version) &&
		fontInfo->LoadFromStream( input ) &&
		this->LoadSimpleType<wxUint32>( input, mCurrentSymbol );

	if ( res )
	{
		SetInfo( fontInfo );
	}

	return res;
}



/* override */ OriginPtr FontEditor::GetOrigin() const
{
	return mCurrentFont ? mCurrentFont->GetOrigin() : nullptr;
}



/* override */ void FontEditor::SetInfo( IInfoPtr info )
{
	FontInfoPtr newFont = std::static_pointer_cast<FontInfo>( info );
	ClearFont();
	mCurrentFont = newFont->Clone();
	UpdateFont();
	SetPaletteAsMain();
	mSymbolEditor->Enable();
}



/* virtual */ bool FontEditor::SaveEditor()
{
	bool res = false;

	if (!mCurrentFont )
	{
		wxLogWarning("Font is not ready to save!");
	}
	else
	{
		wxFileDialog dlg( this, "Save font as...", wxEmptyString, "fontfile", UTT_FONT_EXTENSIONS, wxFD_SAVE | wxFD_OVERWRITE_PROMPT );

		if (dlg.ShowModal() == wxID_OK)
		{
			// mChanged flag can be set true only as Project part... or not?
			//Changed( mCurrentFont->SaveToFile( dlg.GetPath() ) );
			res  = this->SaveToFile( dlg.GetPath() );
		}
	}
	return res;
}



/* virtual */ bool FontEditor::LoadEditor()
{
	bool res = false;
	wxFileDialog dlg( this, "Open UTT font...", wxEmptyString, "fontfile", UTT_FONT_EXTENSIONS, wxFD_OPEN|wxFD_FILE_MUST_EXIST );

	if (dlg.ShowModal() == wxID_OK)
	{
		res = LoadFromFile( dlg.GetPath() );
		/*
		FontInfo* fontInfo = new FontInfo();

		if ( fontInfo->LoadFromFile(  ) )
		{
			SetInfo( fontInfo );
			res = true;
		}
		delete fontInfo;*/
	}

	return res;
}



/* virtual */ void FontEditor::OnBtnClick( wxCommandEvent& event )
{
	switch (event.GetId())
	{

		case wxID_SAVE_BTN:
			SaveEditor();
		break;

		case wxID_LOAD_BTN:
			LoadEditor();
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


//
///* virtual */ void FontEditor::OnFontChangeEvent( ChangeFontEvent& event )
//{
//	this->SetInfo( event.GetFontInfo() );
//	event.Skip();
//}



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
			this->Changed();
		break;

		case EditorRebuildDataEvent::whIndexMaskChanged:
			CurrentSymbolChanged();
			this->Changed();
		break;

		default:
			//wxLogError("FontEditor::OnRebuildDataEvent error: unknown \"what to do\" id (%d)", event.GetWhat());
		break;
	}

	event.Skip();
}