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
#include "luacontrol.h"



const wxString sCommandNames[iecNum] = 
{
	"Import",
	"Export"
};


const wxString	PROJECTNAME = "Project";
const int		PROJECTVERSION = 0x100;



Project::Project():
	IStateStore( PROJECTNAME, PROJECTVERSION ),
	mChanged( false ),
	mProjectName( wxEmptyString ),
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
	mProjectName( other.mProjectName ),
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



bool Project::CreateProject( const wxString& fullPath )
{
	wxFile file;

	if ( !file.Create( fullPath, true ) )
	{
		wxLogError("Project::CreateProject: can't create file %s", fullPath);
		return false;
	}
	
	file.Close();

	wxString vol, path, name, ext;
	wxFileName::SplitPath( fullPath, &vol, &path, &name, &ext );

	mProjectName = name;
	mProjectFileName = fullPath;
	mModuleName = wxEmptyString;
	mModuleVersion = wxEmptyString;
	mLastDir = vol + wxFileName::GetVolumeSeparator( wxPATH_NATIVE ) + path;
	mChanged = false;

	return true;
}



bool Project::SaveProject()
{
	return true;
}



// TODO: implement it, high priority
bool Project::IsAllowed( IECommands what, EditorType who )
{
	wxString command = GetFunctionName(what, who);

	bool result = false;

	if ( !Lua::Get().call( "hasModuleCommand", command.ToStdString() ) || 
		!OOLUA::pull2cpp( Lua::Get(), result ) )
	{
		wxLogError("Project::IsAllowed: error occured");
		Lua::ShowLastError();
	}

	return result;
}



bool Project::Do( IECommands what, EditorType who )
{
	wxString command = GetFunctionName(what, who);

	bool result = Lua::Get().call( command.ToStdString() );

	if ( !result )
	{
		Lua::ShowLastError();
	}

	return result;
}



wxString Project::GetFunctionName( IECommands what, EditorType who )
{
	wxASSERT( what < iecNum && who < etNum );
	return sCommandNames[what] + sEditorNames[who];
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
