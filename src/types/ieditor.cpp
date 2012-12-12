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



IEditor::IEditor( wxWindow* parent, EditorType edtype, const wxString& name ):
	mParent( parent ),
	mEditorType( edtype ),
	mChanged( false ),
	mEditorName( name )
{
}



IEditor::IEditor( const IEditor& other ):
	mParent( other.mParent ),
	mEditorType( other.mEditorType ),
	mChanged( other.mChanged ),
	mEditorName( other.mEditorName )
{
}



/* virtual */ IEditor::~IEditor()
{
	CheckChanged();
}



/* virtual */ int IEditor::CheckChanged()
{
	wxString message = mEditorName + " modified";
	int res = wxMessageDialog(mParent, "Save changes?", message, wxYES_NO | wxCANCEL | wxCENTRE | wxCANCEL_DEFAULT).ShowModal();

	if (res == wxID_YES)
	{
		this->SaveEditor();
	}

	return res;
}