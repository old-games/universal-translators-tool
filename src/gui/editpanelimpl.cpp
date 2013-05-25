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
#include "types/indexmask.h"
#include "palholderctrl.h"

const wxString	UUT_IMAGE_EXTENSIONS = "UTT Image files (*.uim)|*.uim";

ImageEditor::ImageEditor(  wxWindow* parent, ImageEditorMode mode, wxWindowID eventsId /* wxID_ANY */ ):
	EditPanelGui( parent ),
	IEditor( this, etImage, "Image editor" ),
	mEditPanel( NULL ),
	mPalettePanel( NULL ),
	mMode( mode )
{
	if (eventsId == wxID_ANY)
	{
		eventsId = this->GetId();
	}

	mEditPanel = new EditPanel( mEditScrolledBack, eventsId );
	SetEditPanel( mEditPanel );

	mPalettePanel = new PaletteHolderCtrl(mEditScrolledBack, eventsId, this, mEditSizer);
	mPalSizer->Add( mPalettePanel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );

	//wxTheApp->Bind( uttEVT_CHANGEIMAGE, &ImageEditor::OnImageChangeEvent, this, eventsId );
	wxTheApp->Bind( uttEVT_REBUILDDATA, &ImageEditor::OnRebuildDataEvent, this, eventsId );
	
	mSaveBtn->Show( mMode == iemFullMode );
	mLoadBtn->Show( mMode == iemFullMode );
}



ImageEditor::~ImageEditor(void)
{
	//wxTheApp->Unbind( uttEVT_CHANGEIMAGE, &ImageEditor::OnImageChangeEvent, this );
	wxTheApp->Unbind( uttEVT_REBUILDDATA, &ImageEditor::OnRebuildDataEvent, this );
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



void ImageEditor::UpdateImage()
{
	mEditPanel->ResetIndexedBitmap();
}



bool ImageEditor::CheckChanges()
{
	return true;
}



///* virtual */ void ImageEditor::OnImageChangeEvent( ChangeImageEvent& event )
//{
//	SetInfo( event.GetImageInfo() );
////	event.Skip();
//}



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
			SaveEditor();
		break;

		case wxID_LOAD_BTN:
			LoadEditor();
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
		case EditorRebuildDataEvent::whEditColourChanged:
			if (event.GetColour() != NULL)
			{
				mEditPanel->SetEditColour( event.GetBool(), *event.GetColour() );
			}
		break;

		case EditorRebuildDataEvent::whPaletteChanged:
			ChangeImagePalette( event.GetPalette() );
		break;

		default:
			event.Skip();
			//wxLogError("ImageEditor::OnRebuildDataEvent error: unknown \"what to do\" id (%d)", event.GetWhat());
		break;
	}

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
		ChangePaletteEvent palEvent( this->GetId(), pal, false );
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



/* virtual */ bool ImageEditor::SaveState( wxOutputStream& output )
{
	if (!mEditPanel->mImageInfo || !mEditPanel->mImageInfo->IsOk())
	{
		return false;
	}

	bool result = IEditor::SaveState(output) &&
		mEditPanel->mImageInfo->SaveToStream(output);

	if (result)
	{
		this->Changed( false );
	}

	return result;
}



/* virtual */ bool ImageEditor::LoadState( wxInputStream& input, int version )
{
	ImageInfo* imageInfo = new ImageInfo();

	bool res = IEditor::LoadState( input, version ) && 
		imageInfo->LoadFromStream( input );

	if ( res && imageInfo->IsOk() )
	{
		SetInfo(imageInfo);
	}

	delete imageInfo;

	return res;
}



/* virtual */ const Origin* ImageEditor::GetOrigin() const
{
	return mEditPanel->mImageInfo ? mEditPanel->mImageInfo->GetOrigin() : NULL;
}



/* virtual */ void ImageEditor::SetInfo( IInfo* info )
{
	ImageInfo* newImage = static_cast<ImageInfo*>( info );

	ClearImage();
	mEditPanel->SetIndexedBitmap(  newImage	);
	SetPaletteAsMain();
}



/* virtual */ bool ImageEditor::SaveEditor()
{
	bool res = false;

	if (!mEditPanel->mImageInfo || !mEditPanel->mImageInfo->IsOk())
	{
		wxLogWarning("Image is not ready to save!");
		return res;
	}

	wxFileDialog dlg( this, "Save image as...", wxEmptyString, "fileimage", UUT_IMAGE_EXTENSIONS, wxFD_SAVE | wxFD_OVERWRITE_PROMPT );

	if (dlg.ShowModal() == wxID_OK)
	{
		res = mEditPanel->mImageInfo->SaveToFile( dlg.GetPath() );
	}

	return res;
}



/* virtual */ bool ImageEditor::LoadEditor()
{
	bool res = false;

	wxFileDialog dlg( this, "Open UTT image...", wxEmptyString, "fileimage", UUT_IMAGE_EXTENSIONS, wxFD_OPEN|wxFD_FILE_MUST_EXIST );

	if (dlg.ShowModal() == wxID_OK)
	{
		ImageInfo* imageInfo = new ImageInfo();
		imageInfo->LoadFromFile( dlg.GetPath() );

		if ( imageInfo->IsOk() )
		{
			SetInfo(imageInfo);
			res = true;
		}

		delete imageInfo;
	}

	return res;
}
