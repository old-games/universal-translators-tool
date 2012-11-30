/***************************************************************
 * Name:      editpanelimpl.cpp
 * Purpose:   Code for ImageEditor Class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-02-29
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "editpanelimpl.h"
#include "panels/editpanel.h"
#include "types/imageinfo.h"
#include "types/palette.h"


ImageEditor::ImageEditor(  wxWindow* parent, wxWindowID id ):
	EditPanelGui( parent ),
	mEditPanel( NULL )
{
	mEditPanel = new EditPanel( mEditScrolledBack );
	SetEditPanel( mEditPanel );
	wxTheApp->Bind( uttEVT_CHANGEIMAGE, &ImageEditor::OnImageChangeEvent, this );
	wxTheApp->Bind( uttEVT_REBUILDDATA, &ImageEditor::OnRebuildDataEvent, this, id );
}



ImageEditor::~ImageEditor(void)
{
	wxTheApp->Unbind( uttEVT_CHANGEIMAGE, &ImageEditor::OnImageChangeEvent, this );
	wxTheApp->Unbind( uttEVT_REBUILDDATA, &ImageEditor::OnRebuildDataEvent, this, this->GetId() );
//	ClearImage( true );
}



void ImageEditor::SetBitmap( wxBitmap* bitmap )
{
	mEditPanel->SetBitmap( (wxBitmap*) bitmap );
}



void ImageEditor::ClearImage( bool force /* false */ )
{
	if (!CheckChanges() && !force)
	{
		return;
	}
	mEditPanel->DestroyBitmap();
}



void ImageEditor::SetImage( ImageInfo* newImage )
{
	ClearImage();
	mEditPanel->SetIndexedBitmap(  newImage	);
	SetPaletteAsMain();
}



void ImageEditor::UpdateImage()
{
	mEditPanel->ResetIndexedBitmap();
}



bool ImageEditor::CheckChanges()
{
	return true;
}



void ImageEditor::SaveImage()
{
	if (!mEditPanel->mImageInfo->IsOk())
	{
		wxLogWarning("Image is not ready to save!");
		return;
	}

	wxFileDialog dlg( this, "Save image as...", wxEmptyString, "fileimage", "*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
	if (dlg.ShowModal() == wxID_OK)
	{
		mEditPanel->mImageInfo->SaveToFile( dlg.GetPath() );
	}
}



void ImageEditor::LoadImage()
{
}


/* virtual */ void ImageEditor::OnImageChangeEvent( ChangeImageEvent& event )
{
	SetImage( event.GetImageInfo() );
//	event.Skip();
}



/* virtual */ void ImageEditor::OnCommandEvent( wxCommandEvent& event )
{
	switch (event.GetId())
	{
		case wxID_GRID_CHECK:
			SetGridEnabled();
		break;

		case wxID_GRID_MODE:
			SetGridMode();
		break;

		case wxID_GRIDCOL_BTN:
			SetGridColour();
		break;

		case wxID_SAVE_BTN:
			SaveImage();
		break;

		case wxID_LOAD_BTN:
			LoadImage();
		break;

		default:
			wxLogError( wxString::Format("EditPanel::OnCommandEvent: unknown command %d", event.GetId()) );
			return;
	}

	mEditPanel->PaintNow();
	event.Skip();
}


/* virtual */ void ImageEditor::OnRebuildDataEvent( EditorRebuildDataEvent& event )
{
	switch (event.GetWhat())
	{
		case EditorRebuildDataEvent::whPaletteChanged:
			ChangeImagePalette( event.GetPalette() );
		break;

		default:
			wxLogError("ImageEditor::OnRebuildDataEvent error: unknown \"what to do\" id (%d)", event.GetWhat());
		break;
	}

	event.Skip();
}



void ImageEditor::SetGridEnabled()
{
	mEditPanel->SetGridEnabled( mGridCheck->IsChecked() );
}



void ImageEditor::SetGridMode()
{
	switch ( mGridModeChoice->GetSelection() )
	{
		case 0:
			mEditPanel->SetGridLogic( wxCOPY );
		break;

		case 1:
			mEditPanel->SetGridLogic( wxXOR );
		break;

		default:
			wxLogError( wxString::Format("EditPanel::SetGridMode: unknown grid draw logic %d", mGridModeChoice->GetSelection()) );
	}
}



void ImageEditor::SetGridColour()
{
	wxColourData data;
	data.SetChooseFull(true);
	data.SetColour( mEditPanel->GetGridColour() );

	for (int i = 0; i < 16; i++)
	{
		wxColour colour(i*16, i*16, i*16);
		data.SetCustomColour(i, colour);
	}

	wxColourDialog dialog(this, &data);
	if (dialog.ShowModal() == wxID_OK)
	{
		wxColourData retData = dialog.GetColourData();
		mEditPanel->SetGridColour( retData.GetColour() );
	}
}



void ImageEditor::SetEditPanel( EditPanel* editPanel )
{
	if ( !editPanel )
	{
		wxLogError( wxString::Format("ImageEditor::SetEditPanel: bad pointer to EditPanel in args") );
		return;
	}

	if ( mEditPanel && mDrawHolder->Detach( mEditPanel ) )
	{
		delete mEditPanel;
	}
	mEditPanel = editPanel;
	mDrawHolder->Add( mEditPanel, 1, wxEXPAND, 5 );
	mEditPanel->SetAlign( utdHCenter | utdVCenter );
	mEditPanel->Reparent( mEditScrolledBack );
	SetGridEnabled();
	SetGridMode();
}



void ImageEditor::SetPaletteAsMain()
{
	Palette* pal = mEditPanel->mImageInfo->GetPalette();
	if ( pal && pal->IsOk() )
	{
		ChangePaletteEvent palEvent( wxID_IMAGEEDITOR, pal, true );
		wxTheApp->QueueEvent( palEvent.Clone() );
	}
}



void ImageEditor::ChangeImagePalette( Palette* pal )
{
	if (mEditPanel->mImageInfo->SetPalette(pal))
	{
		UpdateImage();
	}
}