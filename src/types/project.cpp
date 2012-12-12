/***************************************************************
 * Name:      project.cpp
 * Purpose:   implementation of Project class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "project.h"


const wxString	PROJECTNAME = "Project";
const int		PROJECTVERSION = 0x100;



Project::Project():
	IStateStore( PROJECTNAME, PROJECTVERSION ),
	mChanged( false ),
	mModuleName( wxEmptyString ),
	mModuleVersion( wxEmptyString ),
	mLastDir( wxEmptyString ),
	mProjectFileName( wxEmptyString ),
	mEditors()
{
}


	
Project::Project( const Project& other ):
	IStateStore( PROJECTNAME, PROJECTVERSION ),
	mChanged( other.mChanged ),
	mModuleName( other.mModuleName ),
	mModuleVersion( other.mModuleVersion ),
	mLastDir( other.mLastDir ),
	mProjectFileName( other.mProjectFileName ),
	mEditors( other.mEditors )
{
}



Project::~Project()
{
}



int Project::CheckChanged()
{
	int res = wxID_YES;

	for (EditorsIterator it = mEditors.begin(); it != mEditors.end(); ++it)
	{
		if ( (*it)->CheckChanged() == wxID_CANCEL )
		{
			return wxID_CANCEL;
		}
	}

	if (mChanged)
	{
		int res = wxMessageDialog(NULL, "Save changes?", "Project modified", wxYES_NO | wxCANCEL | wxCENTRE | wxCANCEL_DEFAULT).ShowModal();

		if (res == wxID_OK)
		{
			mChanged = !SaveProject();
		}
		else
		{
			mChanged = false;
		}

	}
	return res;
}



bool Project::SaveProject()
{
	return true;
}



// TODO: implement it, high priority
bool Project::IsAllowed( IECommands what, EditorType who )
{
	return true;
}



/* virtual */ bool Project::SaveState( wxOutputStream& output )
{
	bool res = true; /*SaveSimpleType<wxInt32>( output, mOriginFrom) &&
		SaveString( output, mOriginFileName ) &&
		SaveString( output, mOriginAdditional );*/

	return res;
}



/* virtual */ bool Project::LoadState( wxInputStream& input, int version )
{
	version;	// unused yet, must exist
	
	
	bool res = true;/*LoadSimpleType<wxInt32>( input, (wxInt32&) mOriginFrom) &&
		LoadString( input, mOriginFileName ) &&
		LoadString( input, mOriginAdditional );*/
	return res;
}
