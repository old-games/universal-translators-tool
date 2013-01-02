/***************************************************************
 * Name:      ieditor.cpp
 * Purpose:   implementation of IEditor interface
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "ieditor.h"
#include "gui/fonteditimpl.h"
#include "gui/editpanelimpl.h"
#include "gui/libwindowimpl.h"



wxWindow* IEditor::sParentWindow = NULL;




const wxString sEditorNames[ etNum ] = 
{
	"Font",
	"Image",
	"Library",
	"Animation",
	"Sound",
	"Video"
};




const int		EDITORVERSION = 0x100;



IEditor::IEditor( wxWindow* parent, EditorType edtype, const wxString& name ):
	IStateStore(name, EDITORVERSION),
	mParent( parent ),
	mEditorType( edtype ),
	mChanged( false ),
	mEditorName( name ),
	mEditorId(-1)
{
}



IEditor::IEditor( const IEditor& other ):
	IStateStore( other ),
	mParent( other.mParent ),
	mEditorType( other.mEditorType ),
	mChanged( other.mChanged ),
	mEditorName( other.mEditorName ),
	mEditorId( other.mEditorId )
{
}



/* virtual */ IEditor::~IEditor()
{
}



wxString IEditor::CreateName()
{
	return wxString::Format("%s_%X", sEditorNames[mEditorType], (wxInt32) mEditorId);
}



void IEditor::CreateEditorId()
{
	// TODO: test casting of this to wxUint32 in x64 builds
	wxString src = wxString::Format("%s_%X", sEditorNames[mEditorType], (wxUint32) this);
	mEditorId = Helpers::crc32buf( src.c_str().AsChar(), src.length() );
}



void IEditor::Changed( bool b /* true */)
{
	if (mChanged != b)
	{
		EditorRebuildDataEvent* event = new EditorRebuildDataEvent(0, EditorRebuildDataEvent::whEditorStateChanged, this, b);
		wxTheApp->QueueEvent( event );
	}

	mChanged = b;
}



/* virtual */ bool IEditor::CheckChanged()
{
	wxString message = mEditorName + " modified";
	int res = wxMessageDialog(mParent, "Save changes?", message, wxYES_NO | wxCANCEL | wxCENTRE | wxCANCEL_DEFAULT).ShowModal();

	if (res == wxID_YES)
	{
		bool done = false;

		while (!done)
		{
			mChanged = !SaveEditor();
			if (mChanged)
			{
				res = wxMessageDialog(mParent, 
					"Retry save changes?", 
					"There was an error while saving " + mEditorName, 
					wxYES_NO | wxCANCEL | wxCENTRE | wxYES_DEFAULT).ShowModal();
				done = res == wxID_NO || res == wxID_CANCEL;
			}
			else
			{
				done = true;
			}
		}
	}

	if (res == wxID_NO)
	{
		mChanged = false;
	}
	
	return res != wxID_CANCEL;
}



/* virtual */ bool IEditor::SaveState( wxOutputStream& output )
{
	bool res = SaveSimpleType<wxInt32>(output, mEditorType) &&
		SaveSimpleType<wxInt32>(output, mEditorId);

	return res;
}



/* virtual */ bool IEditor::LoadState( wxInputStream& input, int version )
{
	version;

	bool res = LoadSimpleType<wxInt32>(input, (wxInt32&) mEditorType) && 
		LoadSimpleType<wxInt32>(input, mEditorId);

	return res;
}



/* static */ IEditor* IEditor::CreateEditor( EditorType edType, bool createId /* true */ )
{

#ifndef RELEASE
	wxStopWatch sw;
#endif

	IEditor* result = NULL;

	switch (edType)
	{
		case etFont:
			result = static_cast<IEditor*> ( new FontEditor( sParentWindow ) );
			break;

		case etImage:
			result = static_cast<IEditor*> ( new ImageEditor( sParentWindow ) );
			break;
		
		case etLibrary:
			result = static_cast<IEditor*> ( new LibraryPanel( sParentWindow ) );
			break;

		default:
			wxLogError("IEditor::CreateEditor: unable to create editor %d", edType);
	}

	if (result && createId)
	{
		result->GetWindow()->Hide();
		result->CreateEditorId();
	}

#ifndef RELEASE
	wxLogMessage("IEditor::CreateEditor %ldms", sw.Time());
#endif

	return result;
}



/* static */ IEditor* IEditor::CreateEditor( wxInputStream& input )
{
	EditorType edType = etNum;
	IEditor* result = NULL;

	wxFileOffset offs = input.TellI();

	if ( SkipHeader(input) && LoadSimpleType<wxInt32>(input, (wxInt32&) edType) )
	{
		result = CreateEditor( edType, false );
	}

	input.SeekI( offs, wxFromStart );

	return result;
}