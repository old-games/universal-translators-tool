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
	mGamePath( wxEmptyString ),
	mProjectFileName( wxEmptyString ),
	mPerspective( wxEmptyString ),
	mEditors()
{
	BindEvents();
}


	
Project::Project( const Project& other ):
	IStateStore( PROJECTNAME, PROJECTVERSION ),
	mChanged( other.mChanged ),
	mProjectName( other.mProjectName ),
	mModuleName( other.mModuleName ),
	mModuleVersion( other.mModuleVersion ),
	mLastDir( other.mLastDir ),
	mProjectFileName( other.mProjectFileName ),
	mPerspective( other.mPerspective ),
	mEditors( other.mEditors )
{
	BindEvents();
}



Project::~Project()
{
	wxTheApp->Unbind(uttEVT_CHANGEINFO, &Project::OnChangeInfoEvent, this);
	wxTheApp->Unbind(uttEVT_REBUILDDATA, &Project::OnEditorRebuildDataEvent, this);
}



void Project::BindEvents()
{
	wxTheApp->Bind(uttEVT_CHANGEINFO, &Project::OnChangeInfoEvent, this);
	wxTheApp->Bind(uttEVT_REBUILDDATA, &Project::OnEditorRebuildDataEvent, this);
}



bool Project::CheckChanged()
{
	bool hasUnsavedEditors = false;

	for (EditorsIterator it = mEditors.begin(); it != mEditors.end(); ++it)
	{
		if ( (*it)->IsChanged() )
		{
			hasUnsavedEditors = true;
			break;
		}
	}

	int res = wxID_YES;

	if (mChanged || hasUnsavedEditors)
	{
		res = wxMessageDialog(NULL, "Save changes?", "Project modified", wxYES_NO | wxCANCEL | wxCENTRE | wxCANCEL_DEFAULT).ShowModal();

		if (res == wxID_YES)
		{
			mChanged = !SaveProject();
		}

		if (res == wxID_NO)
		{
			mChanged = false;
		}
	}

	return res != wxID_CANCEL;
}



bool Project::CreateProject( const wxString& fullPath, const wxString& gamePath, const wxString& module, const wxString& version )
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
	mGamePath = gamePath;
	SetActiveModule( module, version );
	mLastDir = vol + wxFileName::GetVolumeSeparator( wxPATH_NATIVE ) + path;

	return SaveProject();
}



bool Project::SetActiveModule()
{
	bool res = Lua::Get().call( "setCurrentModule", mModuleName.ToStdString(), mGamePath.ToStdString() );
	
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



bool Project::SaveProject( const wxString& saveAs /* wxEmptyString */)
{
	if (!saveAs.IsEmpty())
	{
		mProjectFileName = saveAs;
	}

	bool result = SaveToFile( mProjectFileName );

	if (result)
	{
		mChanged = false;
	}
	return result;
}



bool Project::LoadProject( const wxString& fullPath )
{
	bool result = false;

	if ( CheckChanged() )
	{
		result = LoadFromFile( fullPath );

		for (EditorsIterator it = mEditors.begin(); it != mEditors.end(); ++it)
		{
			AddEditorWindow( *it, (*it)->CreateName(), false );
		}

		SendUpdateEvent();

		mProjectFileName = fullPath;
		SetActiveModule();
		mChanged = false;
	}

	return result;
}



void Project::ReparentEditorWindows( wxWindow* wnd )
{
	for (EditorsIterator it = mEditors.begin(); it != mEditors.end(); ++it)
	{
		(*it)->GetWindow()->Reparent( wnd );
	}
}



void Project::CloseProject()
{
	EditorsIterator it = mEditors.begin();

	while (it != mEditors.end())
	{
		CloseEditor( *it, false );
		delete *it;
		mEditors.erase(it);
	}

	mChanged = false;

	SendUpdateEvent();
}



void Project::CloseEditor( IEditor* editor, bool update )
{
	AUIWindowEvent event( AUIWindowEvent::RemoveWindow, editor->GetWindow(), update ); 
	wxTheApp->ProcessEvent( event );
}



void Project::RemoveEditor( IEditor* editor )
{
	CloseEditor( editor, true );
	mEditors.Remove( editor );
	delete editor;
	mChanged = true;
	SendUpdateEvent();
}



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



bool Project::SaveEditors( wxOutputStream& output )
{
	bool res = SaveSimpleType<wxUint32>(output, mEditors.size());

	for (EditorsIterator it = mEditors.begin(); it != mEditors.end() && res; ++it)
	{
		res = (*it)->SaveToStream( output );
	}

	return res;
}



bool Project::LoadEditors( wxInputStream& input )
{
	wxUint32 num = 0;
	bool res = LoadSimpleType<wxUint32>(input, num);

	for (size_t i = 0; i < num && res; ++i)
	{
		IEditor* editor = IEditor::CreateEditor( input );
			
		if (editor)
		{
			res = editor->LoadFromStream( input );

			if ( res )
			{
				mEditors.push_back( editor );
			}
		}
		else
		{
			res = false;
		}
	}

	return res;
}



void Project::CreateEditorAndSetIt( IInfo* info )
{
	IEditor* editor = IEditor::CreateEditor( info->GetEditorType(), true );

	if (editor)
	{
		mEditors.push_back( editor );
		editor->SetInfo( info );
		AddEditorWindow( editor, editor->CreateName(), true );

		AUIWindowEvent* event = new AUIWindowEvent( AUIWindowEvent::ShowWindow, 
			editor->GetWindow() );
		wxTheApp->QueueEvent( event );
	}
}



void Project::AddEditorWindow( IEditor* editor, const wxString& wndName, bool update )
{
	AUIWindowEvent addEvent( AUIWindowEvent::AddWindow, editor->GetWindow(), update, wndName ); 
	wxTheApp->ProcessEvent( addEvent );
	SendSetCaptionEvent( editor );
	mChanged = true;
}



void Project::SendSetCaptionEvent( IEditor* editor )
{
	if (editor->GetOrigin())
	{
		AUIWindowEvent* renameEvent = new AUIWindowEvent( AUIWindowEvent::RenameWindow, 
			editor->GetWindow(), false, editor->GetOrigin()->GetFileName() ); 
		wxTheApp->QueueEvent( renameEvent );
	}
}



void Project::SendUpdateEvent()
{
	AUIWindowEvent* event = new AUIWindowEvent ( AUIWindowEvent::UpdateManager ); 
	wxTheApp->QueueEvent( event );
	//AUIWindowEvent event( AUIWindowEvent::UpdateManager ); 
	//wxTheApp->ProcessEvent( event );

}



IEditor* Project::FindEditor( wxWindow* wnd ) const
{
	for (ConstEditorsIterator it = mEditors.begin(); it != mEditors.end(); ++it)
	{
		if ((*it)->GetWindow() == wnd)
		{
			return *it;
		}
	}
	return NULL;
}



/* virtual */ bool Project::SaveState( wxOutputStream& output )
{
	bool res = SaveString( output, mProjectName ) &&
		SaveString( output, mProjectFileName ) &&
		SaveString( output, mModuleName ) &&
		SaveString( output, mModuleVersion ) &&
		SaveString( output, mGamePath ) &&
		SaveString( output, mLastDir ) &&
		SaveString( output, mPerspective);

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
		LoadString( input, mGamePath ) &&
		LoadString( input, mLastDir ) &&
		LoadString( input, mPerspective);

	res = LoadEditors( input );

	return res;
}



/* virtual */ void Project::OnChangeInfoEvent( ChangeInfoEvent& event )
{
	CreateEditorAndSetIt( event.GetInfo() );
	SendUpdateEvent();
	event.Skip();
}



/* virtual */ void Project::OnEditorRebuildDataEvent( EditorRebuildDataEvent& event )
{
	switch (event.GetWhat())
	{
		case EditorRebuildDataEvent::whPaletteChanged:
			wxLogMessage("rebuild palette");
		break;

		case EditorRebuildDataEvent::whEditorStateChanged:
			mChanged = true;
		break;
	}

	event.Skip();
}