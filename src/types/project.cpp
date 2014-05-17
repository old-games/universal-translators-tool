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
#include "panels/videopanel.h"


const wxString sCommandNames[iecNum] = 
{
	"Import",
	"Export"
};



Project::Project():
	IStateStore(),
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
	IStateStore(),
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
	wxTheApp->Unbind(uttEVT_COMMON, &Project::OnCommonEvent, this);
	wxTheApp->Unbind(uttEVT_CHANGEINFO, &Project::OnChangeInfoEvent, this);
	wxTheApp->Unbind(uttEVT_REBUILDDATA, &Project::OnEditorRebuildDataEvent, this);
}



void Project::BindEvents()
{
	wxTheApp->Bind(uttEVT_COMMON, &Project::OnCommonEvent, this);
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
	mLastDir = vol + wxFileName::GetVolumeSeparator( wxPATH_NATIVE ) + path;
	CheckPathDelimiters();
	SetActiveModule( module, version );
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

	bool result = SaveToFile(mProjectFileName);

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
		mProjectFileName = fullPath;
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
	editor->Deinit();
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
	return Helpers::HasModuleFunction(command);
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
	bool res = true;

	for (EditorsIterator it = mEditors.begin(); it != mEditors.end() && res; ++it)
	{
		IEditor* editor = *it;
		OriginPtr info = editor->GetOrigin();
		wxASSERT(info);
		wxString command = GetFunctionName(iecImport, editor->GetType());
		wxString path = info->GetFullPath();
		path.Replace("\\", "/");
		
		res = WriteLine(output, wxString::Format("doModuleCommand('%s', '%s')",
			command, path) );
			
		if (!res)
		{
			break;
		}
	}

	return res;
}



void Project::CreateEditorAndSetIt(IInfoPtr info )
{
	IEditor* editor = IEditor::CreateEditor( info->GetEditorType(), true );

	if (editor)
	{
		mEditors.push_back(editor);
		editor->SetInfo(info);
		AddEditorWindow( editor, editor->CreateName(), true );

		AUIWindowEvent* event = new AUIWindowEvent(
			AUIWindowEvent::ShowWindow, editor->GetWindow() );
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



void Project::CheckPathDelimiters()
{
	mProjectFileName.Replace("\\", "/");
	mGamePath.Replace("\\", "/");
	mLastDir.Replace("\\", "/");
}



/* virtual */ bool Project::SaveState( wxOutputStream& output )
{
	CheckPathDelimiters();
	
	bool res = WriteLine(output, "-- project's name, filename");
	
	res = WriteLine(output, wxString::Format("setProjectName('%s', '%s')\r", 
		mProjectName, mProjectFileName));
	
	res = WriteLine(output, "-- path to game, last used directory in any kind of FileDialog");
	res = WriteLine(output, wxString::Format("setProjectPath('%s', '%s')\r",
		mGamePath, mLastDir));

	res = WriteLine(output, "-- module name, module version");
	res = WriteLine(output, wxString::Format("setProjectModule('%s', '%s')\r",
		mModuleName, mModuleVersion));

	res = SaveEditors(output);

	return res;
}



/* virtual */ bool Project::LoadState( wxInputStream& input, int version )
{
	version;	// unused yet, must exist
	
	size_t size = input.GetSize();
	char* buf = new char[size + 1];
	memset(buf, 0, size + 1);
	input.Read(buf, size);
	bool res = Lua::Get().run_chunk(buf);
	
	if (!res)
	{
		Lua::ShowLastError();
	}
	
	delete[] buf;
	return res;
}



void Project::OnCommonEvent( CommonEvent& event )
{
	const wxArrayString& params = event.GetParams();
	
	switch(event.GetAction())
	{
		case CommonEvent::ceSetProjectName:
			wxASSERT(params.size() == 2);
			mProjectName = params[0];
			mProjectFileName = params[1];
		break;
		
		case CommonEvent::ceSetProjectPath:
			wxASSERT(params.size() == 2);
			mGamePath = params[0];
			mLastDir = params[1];
		break;
		
		case CommonEvent::ceSetProjectModule:
			wxASSERT(params.size() == 2);
			mModuleName = params[0];
			mModuleVersion = params[1];
			SetActiveModule();
		break;
		
		default:
			wxLogDebug("Project::OnCommonEvent: unknown event action %d", event.GetAction());
	}
	event.Skip();
}



void Project::OnChangeInfoEvent( ChangeInfoEvent& event )
{
	CreateEditorAndSetIt( event.GetInfo() );
	SendUpdateEvent();
	event.Skip();
}



void Project::OnEditorRebuildDataEvent( EditorRebuildDataEvent& event )
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