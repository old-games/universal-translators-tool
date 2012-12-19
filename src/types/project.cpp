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

#include "gui/fonteditimpl.h"
#include "gui/logwindowimpl.h"
#include "gui/editpanelimpl.h"
#include "gui/palwindowimpl.h"
#include "gui/libwindowimpl.h"

wxWindow* Project::sParentWindow = NULL;

const wxString sCommandNames[iecNum] = 
{
	"Import",
	"Export"
};


const wxString	PROJECTNAME = "Project";
const int		PROJECTVERSION = 0x100;



Project::Project():
	IStateStore( PROJECTNAME, PROJECTVERSION ),
	//wxEvtHandler(),
	mChanged( false ),
	mProjectName( wxEmptyString ),
	mModuleName( wxEmptyString ),
	mModuleVersion( wxEmptyString ),
	mLastDir( wxEmptyString ),
	mProjectFileName( wxEmptyString ),
	mEditors()
{
	wxTheApp->Bind(uttEVT_CHANGEFONT, &Project::OnChangeFontEvent, this);
}


	
Project::Project( const Project& other ):
	IStateStore( PROJECTNAME, PROJECTVERSION ),
	//wxEvtHandler(),
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



bool Project::CreateProject( const wxString& fullPath, const wxString& module, const wxString& version )
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
	SetActiveModule( module, version );
	mLastDir = vol + wxFileName::GetVolumeSeparator( wxPATH_NATIVE ) + path;
	return SaveProject();
}



bool Project::SetActiveModule()
{
	bool res = Lua::Get().call( "setCurrentModule", mModuleName.ToStdString() );
	
	if (res && !mModuleVersion.IsEmpty())
	{
		res = Lua::Get().call( "setModuleVersion", mModuleVersion.ToStdString() );
	}

	if (!res)
	{
		wxLogError("Project::SetActiveModule: can't set up module %s (version %s)", mModuleName, mModuleVersion);
	}

	return res;
}



bool Project::SetActiveModule( const wxString& module, const wxString& version )
{
	mModuleName = module;
	mModuleVersion = version;
	return SetActiveModule();
}



bool Project::SaveProject()
{
	bool result = false;

	if ( SaveToFile( mProjectFileName ) )
	{
		mChanged = false;
		result = true;
	}

	return result;
}



bool Project::LoadProject( const wxString& fullPath )
{
	bool result = false;

	if ( CheckChanged() )
	{
		result = LoadFromFile( fullPath );
		mProjectFileName = fullPath;
		SetActiveModule();
	}

	return result;
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

	bool result = Lua::Get().call( "doModuleCommand", command.ToStdString() );

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



IEditor* Project::CreateEditor( EditorType who )
{
	IEditor* result = NULL;

	switch (who)
	{
		case etFont:
			result = static_cast<IEditor*> ( new FontEditor(NULL) );
		break;

		case etImage:
			//result = static_cast<IEditor*> ( new ImageEditor(NULL) );
		break;

		default:
			wxLogError("Project::CreateEditor: unable to create editor %d", who);
	}

	return result;
}



bool Project::SaveEditors( wxOutputStream& output )
{
	bool res = SaveSimpleType<wxUint32>(output, mEditors.size());

	for (EditorsIterator it = mEditors.begin(); it != mEditors.end() && res; ++it)
	{
		res = SaveSimpleType<wxInt32>(output, (*it)->GetType()) && (*it)->SaveEditor( output );
	}

	return res;
}



bool Project::LoadEditors( wxInputStream& input )
{
	wxUint32 num = 0;
	bool res = LoadSimpleType<wxUint32>(input, num);

	for (size_t i = 0; i < num && res; ++i)
	{
		wxInt32 edType = (wxInt32) etNum;
		res = LoadSimpleType<wxInt32>(input, edType);

		if (res)
		{
			IEditor* editor = CreateEditor( (EditorType) edType );
			
			if (editor)
			{
				res = editor->LoadEditor( input );
			}
			else
			{
				res = false;
			}
		}
	}

	return res;
}



void Project::CreateFontEditor( FontInfo* info )
{
	FontEditor* fe = new FontEditor( sParentWindow );
	AddEditorWindow( fe, fe, "Font editor" );
	fe->SetFont(info);
}



void Project::AddEditorWindow( wxWindow* wnd, IEditor* editor, const wxString& name )
{
	AddAUIWindowEvent* event = new AddAUIWindowEvent(wnd, name); 
	wxTheApp->QueueEvent( event );
	mEditors.push_back( editor );
}



/* virtual */ bool Project::SaveState( wxOutputStream& output )
{
	bool res = SaveString( output, mProjectName ) &&
		SaveString( output, mProjectFileName ) &&
		SaveString( output, mModuleName ) &&
		SaveString( output, mModuleVersion ) &&
		SaveString( output, mLastDir );

	res = SaveEditors( output );

	return res;
}



/* virtual */ bool Project::LoadState( wxInputStream& input, int version )
{
	version;	// unused yet, must exist
	
	bool res = LoadString( input, mProjectName ) &&
		LoadString( input, mProjectFileName ) &&
		LoadString( input, mModuleName ) &&
		LoadString( input, mModuleVersion ) &&
		LoadString( input, mLastDir );

	res = LoadEditors( input );

	return res;
}



/* virtual */ void Project::OnChangeFontEvent( ChangeFontEvent& event )
{
	CreateFontEditor( event.GetFontInfo() );
	event.Skip();
}