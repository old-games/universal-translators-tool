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



const wxString sEditorNames[ etNum ] = 
{
	"Font",
	"Image",
	"Library",
	"Animation",
	"Sound",
	"Video"
};


IEditor::IEditor( wxWindow* parent, EditorType edtype, const wxString& name ):
	mParent( parent ),
	mEditorType( edtype ),
	mChanged( false ),
	mEditorName( name ),
	mEditorId(-1)
{
}



IEditor::IEditor( const IEditor& other ):
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