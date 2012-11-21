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


ImageEditor::ImageEditor(  wxWindow* parent ):
	EditPanelGui( parent ),
	mEditPanel( NULL ),
	mImageInfo( NULL )
{
	mEditPanel = new EditPanel( mEditScrolledBack );
	SetEditPanel( mEditPanel );
	wxTheApp->Bind( uttEVT_CHANGEIMAGE, &ImageEditor::OnImageChangeEvent, this );
}



ImageEditor::~ImageEditor(void)
{
	wxTheApp->Unbind( uttEVT_CHANGEIMAGE, &ImageEditor::OnImageChangeEvent, this );
	ClearImage( true );
}



void ImageEditor::SetBitmap( wxBitmap* bitmap )
{
	mEditPanel->SetBitmap( (wxBitmap*) bitmap );
}



void ImageEditor::ClearImage( bool force /* false */ )
{
	if (mImageInfo != NULL)
	{
		if (!CheckChanges() && !force)
		{
			return;
		}
		delete mImageInfo;
		mImageInfo = NULL;
	}
}



void ImageEditor::SetImage( ImageInfo* newImage )
{
	ClearImage();
	mImageInfo = newImage->Clone();
	UpdateImage();
	mImageInfo->SetPaletteAsMain();
}



void ImageEditor::UpdateImage()
{
	mEditPanel->SetIndexedBitmap( mImageInfo );
}



bool ImageEditor::CheckChanges()
{
	return true;
}



/* virtual */ void ImageEditor::OnImageChangeEvent( ChangeImageEvent& event )
{
	SetImage( event.GetImageInfo() );
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

		default:
			wxLogError( wxString::Format("EditPanel::OnCommandEvent: unknown command %d", event.GetId()) );
			return;
	}
	mEditPanel->PaintNow();
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
