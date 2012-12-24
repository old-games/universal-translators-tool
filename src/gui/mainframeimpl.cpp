/************************************************************************************
 * Name:      mainframeimpl.cpp
 * Purpose:   Code for MainFrameImpl Class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-01-17
 * Copyright: Pavlovets Ilia
 * License:
*
 * Notes to whole project:
 *		- we are not using STL except std::string in OOLUA functions
 *		- we are using iterators in wxARRAY because they are faster than [] operator
 ************************************************************************************/



#include "pch.h"
#include "mainframeimpl.h"
#include "luacontrol.h"
#include "types/undo.h"
#include "types/imageinfo.h"
#include "types/project.h"


#include "createdlgimpl.h"

#include "panels/symbolpanel.h"

#define MODULE_MENU_START	(wxID_HIGHEST + 1)
#define MODULE_MENU_END		(MODULE_MENU_START + 32)

const wxString PROJECT_EXTENSIONS = "UTT Project file (*.UTTPROJ)|*.uttproj";

MainFrameImpl::MainFrameImpl(void):
	UttMainFrame(0L),
	mHelpController( NULL ),
	mCurrentProject( NULL ),
	mCurrentPane( NULL )
{
	
	COMMAND->SetEditMenu( mEditMenu );
	COMMAND->Initialize();

//		wxBMPHandler: For loading (including alpha support) and saving, always installed.
//		wxPNGHandler: For loading and saving. Includes alpha support.
//		wxJPEGHandler: For loading and saving.
//		wxGIFHandler: For loading and saving (see below).
//		wxPCXHandler: For loading and saving (see below).
//		wxPNMHandler: For loading and saving (see below).
//		wxTIFFHandler: For loading and saving. Includes alpha support.
//		wxTGAHandler: For loading and saving. Includes alpha support.
//		wxIFFHandler: For loading only.
//		wxXPMHandler: For loading and saving.
//		wxICOHandler: For loading and saving.
//		wxCURHandler: For loading and saving.
//		wxANIHandler: For loading only.

	wxImage::AddHandler(new wxPNGHandler);
	wxImage::AddHandler(new wxJPEGHandler);
	wxImage::AddHandler(new wxGIFHandler);
	wxImage::AddHandler(new wxPCXHandler);
	wxImage::AddHandler(new wxPNMHandler);
	wxImage::AddHandler(new wxTGAHandler);
	wxImage::AddHandler(new wxTIFFHandler);
	wxImage::AddHandler(new wxIFFHandler);
	wxImage::AddHandler(new wxXPMHandler);


	this->Bind( wxEVT_IDLE, &MainFrameImpl::OnIdle, this );
	this->Bind( wxEVT_SHOW, &MainFrameImpl::OnShow, this );
	this->Bind( wxEVT_AUI_PANE_ACTIVATED, &MainFrameImpl::OnAUIManagerEvent, this );

	wxTheApp->Bind( uttEVT_MODULECHANGED, &MainFrameImpl::OnModuleChanged, this );
	wxTheApp->Bind( uttEVT_ADDAUIWINDOW, &MainFrameImpl::OnAUIWindowEvent, this );
	wxTheApp->Bind( uttEVT_REBUILDDATA, &MainFrameImpl::OnEditorRebuildDataEvent, this);

	m_mgr.Update();
	UpdateMenuStates();

	wxWindow* hiddenPanel = new wxWindow( this, wxID_ANY );	// this is hack for new windows creating
	hiddenPanel->Hide();					// if parent is hidden - no flickering on window construction
	IEditor::sParentWindow = hiddenPanel;	// MainFrame will delete it automatically on exit
	// may be it needs just a little research of wxWidgets functionality so TODO it someday
}



MainFrameImpl::~MainFrameImpl(void)
{
	this->Unbind( wxEVT_IDLE, &MainFrameImpl::OnIdle, this );
	this->Unbind( wxEVT_SHOW, &MainFrameImpl::OnShow, this );
	this->Unbind( wxEVT_AUI_PANE_ACTIVATED, &MainFrameImpl::OnAUIManagerEvent, this );

	wxTheApp->Unbind( uttEVT_ADDAUIWINDOW, &MainFrameImpl::OnAUIWindowEvent, this );
	wxTheApp->Unbind( uttEVT_MODULECHANGED, &MainFrameImpl::OnModuleChanged, this );
	wxTheApp->Unbind(uttEVT_REBUILDDATA, &MainFrameImpl::OnEditorRebuildDataEvent, this);

}



void MainFrameImpl::OnModuleChanged( ModuleChangedEvent& event )
{
	DoModuleChanged();
	event.Skip();
}



void MainFrameImpl::AddPane( wxWindow* wnd, const wxString& name, bool show)
{
	if (wnd)
	{
		wnd->Reparent(this);
		m_mgr.AddPane( wnd, wxAuiPaneInfo().Name(name).Show( show ).
			Center().
			MaximizeButton( true ).
			PinButton( true ).
			Dock().
			Resizable().
			FloatingSize( wxDefaultSize ).
			DockFixed( false ) );
	}
}



void MainFrameImpl::Init()
{
	wxLogMessage( "Initiating UTT" );
	if (!Lua::Init())
	{
		Lua::ShowLastError();
	}

	mHelpController = new wxHelpController( this );
	if (!mHelpController->Initialize( "utt.chm" ))
	{
		wxLogError("Help was not initialized! UTT.CHM lost?");
		delete mHelpController;
		mHelpController = NULL;
	}

	UpdateMenuStates();
}



void MainFrameImpl::Deinit()
{
	ImageInfo::Done();

	if (mHelpController)
	{
		delete mHelpController;
		mHelpController = NULL;
	}

	Lua::Done();
	wxLogMessage( "UTT exits" );
}



void MainFrameImpl::DoOpenProject()
{
	
	wxFileDialog dlg(this, "Open project", wxEmptyString, wxEmptyString, PROJECT_EXTENSIONS, wxFD_OPEN|wxFD_FILE_MUST_EXIST);

	if ( dlg.ShowModal() != wxID_OK || !DoCloseProject() )
	{
		return;
	}

	Project* old = mCurrentProject;
	Project* newProject = new Project();

	if (!newProject->LoadProject( dlg.GetPath() ))
	{
		delete newProject;
		newProject = old;
		wxLogError("MainFrameImpl::DoOpenProject: there was an error(s). Project NOT loaded!");
	}

	mCurrentProject = newProject;

	mProjectWindow->SetProject( mCurrentProject );
	m_mgr.GetPane( mProjectWindow ).Caption( "Project: " + mCurrentProject->GetName() );
	m_mgr.LoadPerspective( mCurrentProject->GetPerspective() );
	m_mgr.Update();
	UpdateMenuStates();
}



void MainFrameImpl::DoSelectModule()
{
	if ( !Lua::Get().call( "selectModule" ) )
	{
		Lua::ShowLastError();
		return;
	}
}



void MainFrameImpl::DoSelectVersion()
{
	if ( !Lua::Get().call( "selectVersion" ) )
	{
		Lua::ShowLastError();
		return;
	}
}



bool MainFrameImpl::DoCloseProject(bool force /* true */)
{
	bool result = true;

	if (mCurrentProject != NULL)
	{	
		if ( force || CheckProject() )
		{
			mCurrentProject->CloseProject();
			delete mCurrentProject;
			mCurrentProject = NULL;

			mProjectWindow->SetProject( NULL );
			m_mgr.GetPane( mProjectWindow ).Caption( "No active project" );
			COMMAND->ClearCommands();
		}
		else
		{
			result = false;
		}
	}

	return result;
}



bool MainFrameImpl::CheckProject()
{
	if (!mCurrentProject)
	{
		return true;
	}

	return mCurrentProject->CheckChanged();
}



void MainFrameImpl::CreateNewProject()
{
	if ( !DoCloseProject() )
	{
		return;
	}

	CreateProjectDlg dlg;

	if (!dlg.IsReady() || dlg.ShowModal() != wxID_OK)
	{
		return;
	}

	mCurrentProject = new Project();
	mCurrentProject->CreateProject( dlg.GetPath(), dlg.GetGamePath(), dlg.GetModule(), dlg.GetVersion() );

	mProjectWindow->SetProject( mCurrentProject );
	m_mgr.GetPane( mProjectWindow ).Caption( "Project: " + mCurrentProject->GetName() );

	UpdateMenuStates();
	COMMAND->ClearCommands();
}



void MainFrameImpl::DoSaveProject( bool saveAs /* false */)
{
	if (!mCurrentProject)
	{
		return;
	}

	wxString projName = mCurrentProject->GetProjectFileName();
	if (saveAs)
	{
		wxFileDialog dlg( this, "Save project as...", wxEmptyString, projName, PROJECT_EXTENSIONS, wxFD_SAVE | wxFD_OVERWRITE_PROMPT );

		if (dlg.ShowModal() != wxID_OK)
		{
			return;
		}
		
		projName = dlg.GetPath();
	}

	mCurrentProject->SetPerspective( m_mgr.SavePerspective() );
	mCurrentProject->SaveProject( projName );

	UpdateMenuStates();
}



void MainFrameImpl::DoModuleChanged()
{
	if ( !Lua::Get().call( "getModuleName" ) )
	{
		Lua::ShowLastError();
		return;
	}

	std::string s;

	if ( OOLUA::pull2cpp(Lua::Get(), s ) )
	{
		mStatusBar->SetStatusText(s, 1 );
	}

	wxArrayString res;

	if ( Lua::Get().call( "getModuleMenu" ) )
	{
		Helpers::PullTableOfStrings( res );
	}
	else
	{
		Lua::ShowLastError();
	}
	
	UpdateModuleMenu( res );
}



void MainFrameImpl::DoModuleCommand( int n )
{
	if (!mCurrentProject || !mCurrentPane)
	{
		return;
	}

	IEditor* editor = mCurrentProject->FindEditor( mCurrentPane->window );

	if (editor)
	{
		wxString command = mModuleMenu->GetLabelText(n);

		if ( !Lua::Get().call( "executeModuleMenuCommand", command.ToStdString(), mCurrentPane->window->GetId() ) )
		{
			Lua::ShowLastError();
			return;
		}
	}
	else
	{
		wxLogError("MainFrameImpl::DoModuleCommand: %s window not found in editors!", mCurrentPane->name);
	}
}



void MainFrameImpl::DoShowHide( int id )
{
	wxWindow* wnd = this->FindWindowById( id );
	wxMenuItem* item = mViewMenu->FindItem( id );

	if (!wnd || !item)
	{
		return;
	}

	bool show = item->IsChecked();

	wxAuiPaneInfo& pane = m_mgr.GetPane( wnd );

	if (pane.IsOk())
	{
		pane.Show(show);
		m_mgr.Update();
	}
}



void MainFrameImpl::UpdateViewMenu( wxWindowID id, bool visible )
{
	wxMenuItem* item = mViewMenu->FindItem( id );
	
	if (item)
	{
		item->Check( visible );
	}
}



void MainFrameImpl::ClearModuleMenu()
{
	wxMenuItemList& list = mModuleMenu->GetMenuItems();

	for ( size_t i = 0; i < list.GetCount(); ++i )
	{
		wxMenuItem* item = list[i];
		this->Unbind( wxEVT_COMMAND_MENU_SELECTED, &MainFrameImpl::OnModuleMenuSelect, this, item->GetId() );
		mModuleMenu->Delete(item);
	}
}



void MainFrameImpl::UpdateModuleMenu( const wxArrayString& strings )
{
	wxASSERT( strings.size() + MODULE_MENU_START < MODULE_MENU_END ); 

	ClearModuleMenu();
	for (size_t i = 0; i < strings.size(); ++i)
	{
		wxMenuItem* item = new wxMenuItem( mModuleMenu, MODULE_MENU_START + i, strings[i], wxEmptyString, wxITEM_NORMAL );
		mModuleMenu->Append( item );
		this->Bind( wxEVT_COMMAND_MENU_SELECTED, &MainFrameImpl::OnModuleMenuSelect, this, item->GetId() );
	}
}



void MainFrameImpl::UpdateMenuStates()
{
	bool luaOk = Lua::IsOk();
	bool projectActive = mCurrentProject != NULL && luaOk;
	bool projectChanged = projectActive && mCurrentProject->IsChanged();

	mMainToolBar->EnableTool( wxID_NEW_PROJECT, luaOk );
	mFileMenu->Enable( wxID_NEW_PROJECT,  luaOk );

	mMainToolBar->EnableTool( wxID_OPEN_PROJECT, luaOk );
	mFileMenu->Enable( wxID_OPEN_PROJECT,  luaOk );

	mMainToolBar->EnableTool( wxID_SAVE_PROJECT, projectActive );
	mFileMenu->Enable( wxID_SAVE_PROJECT,  projectActive );
	mFileMenu->Enable( wxID_SAVE_PROJECT_AS,  projectActive );



	mMainToolBar->EnableTool( wxID_IMPORT_FONT, projectActive && mCurrentProject->IsAllowed(iecImport, etFont) );
	mImportExportMenu->Enable( wxID_IMPORT_FONT,  projectActive && mCurrentProject->IsAllowed(iecImport, etFont) );

	mMainToolBar->EnableTool( wxID_IMPORT_IMAGE, projectActive && mCurrentProject->IsAllowed(iecImport, etImage) );
	mImportExportMenu->Enable( wxID_IMPORT_IMAGE,  projectActive && mCurrentProject->IsAllowed(iecImport, etImage) );

	mMainToolBar->EnableTool( wxID_IMPORT_LIBRARY, projectActive && mCurrentProject->IsAllowed(iecImport, etLibrary) );
	mImportExportMenu->Enable( wxID_IMPORT_LIBRARY,  projectActive && mCurrentProject->IsAllowed(iecImport, etLibrary) );

	mMainToolBar->EnableTool( wxID_IMPORT_ANIMATION, projectActive && mCurrentProject->IsAllowed(iecImport, etAnimation) );
	mImportExportMenu->Enable( wxID_IMPORT_ANIMATION,  projectActive && mCurrentProject->IsAllowed(iecImport, etAnimation) );



	mMainToolBar->EnableTool( wxID_EXPORT_FONT, projectActive && mCurrentProject->IsAllowed(iecExport, etFont) );
	mImportExportMenu->Enable( wxID_EXPORT_FONT,  projectActive && mCurrentProject->IsAllowed(iecExport, etFont) );

	mMainToolBar->EnableTool( wxID_EXPORT_IMAGE, projectActive && mCurrentProject->IsAllowed(iecExport, etImage) );
	mImportExportMenu->Enable( wxID_EXPORT_IMAGE,  projectActive && mCurrentProject->IsAllowed(iecExport, etImage) );

	mMainToolBar->EnableTool( wxID_EXPORT_LIBRARY, projectActive && mCurrentProject->IsAllowed(iecExport, etLibrary) );
	mImportExportMenu->Enable( wxID_EXPORT_LIBRARY,  projectActive && mCurrentProject->IsAllowed(iecExport, etLibrary) );

	mMainToolBar->EnableTool( wxID_EXPORT_ANIMATION, projectActive && mCurrentProject->IsAllowed(iecExport, etAnimation) );
	mImportExportMenu->Enable( wxID_EXPORT_ANIMATION,  projectActive && mCurrentProject->IsAllowed(iecExport, etAnimation) );

	mMainToolBar->Refresh();
}



void MainFrameImpl::OnIdle( wxIdleEvent& event)
{
	if (Lua::GetRebootFlag())
	{
		Lua::Done();
		Lua::Init();
		
		if (mCurrentProject)
		{
			mCurrentProject->SetActiveModule();
		}

		UpdateMenuStates();
	}

	event.Skip();
}



void MainFrameImpl::OnShow( wxShowEvent& event )
{
	event.Skip();
	m_mgr.Update();
}



void MainFrameImpl::OnClose( wxCloseEvent& event )
{
	if ( !DoCloseProject() )
	{
		event.Veto();
		return;
	}
	this->Deinit();
	event.Skip();
}



void MainFrameImpl::OnModuleMenuSelect( wxCommandEvent& event )
{
	int id = event.GetId();
	if (id >= MODULE_MENU_START && id < MODULE_MENU_END )
	{
		DoModuleCommand( id );
	}
}



void MainFrameImpl::OnMenuSelect( wxCommandEvent& event )
{
	int id = event.GetId();
	
	IECommands what = iecNum;
	EditorType who = etNum;

	switch ( id )
	{
		case wxID_HELP_HELP:
			if (mHelpController)
			{
				if (!mHelpController->DisplayContents())
				{
					wxLogError("Help was initialized, but can not display contents!");
				}
			}
		break;

		case wxID_NEW_PROJECT:
			CreateNewProject();
		break;

		case wxID_SAVE_PROJECT:
			DoSaveProject();
		break;

		case wxID_SAVE_PROJECT_AS:
			DoSaveProject( true );
		break;


		case wxID_CLOSE_PROJECT:
			if (DoCloseProject())
			{
				UpdateMenuStates();
			}
		break;

		case wxID_FILE_QUIT:
			this->Close();
		break;

		case wxID_LUA_SELECT:
			DoSelectModule();
		break;

		case wxID_LUA_VERSION:
			DoSelectVersion();
		break;

		case wxID_LUA_REBOOT:
			if ( AREYOUSURE("Reboot Lua virtual machine...") == wxID_YES )
			{
				Lua::SetRebootFlag();
			}
		break;

		case wxID_UNDO:
			COMMAND->Undo();
		break;

		case wxID_REDO:
			COMMAND->Redo();
		break;

		case wxID_HELP_ABOUT:
			{
				AboutBoxGui about(this);
				about.ShowModal();
			}
		break;

		case wxID_OPEN_PROJECT:
			DoOpenProject();
		break;

		case wxID_IMPORT_FONT:
			what = iecImport;
			who = etFont;
		break;

		case wxID_IMPORT_IMAGE:
			what = iecImport;
			who = etImage;
		break;

		case wxID_IMPORT_LIBRARY:
			what = iecImport;
			who = etLibrary;
		break;

		case wxID_IMPORT_ANIMATION:
			what = iecImport;
			who = etAnimation;
		break;

		case wxID_EXPORT_FONT:
			what = iecExport;
			who = etFont;
		break;

		case wxID_EXPORT_IMAGE:
			what = iecExport;
			who = etImage;
		break;

		case wxID_EXPORT_LIBRARY:
			what = iecExport;
			who = etLibrary;
		break;

		case wxID_EXPORT_ANIMATION:
			what = iecExport;
			who = etAnimation;
		break;

		case wxID_VIEW_TOOLBAR:
		case wxID_VIEW_LOG:
		case wxID_VIEW_PROJECT:
			DoShowHide( event.GetId() );
		break;

		default:
			wxLogMessage( wxString::Format("Unknown command from main menu: %d", id) );
		break;
	}

	if (mCurrentProject && what < iecNum && who < etNum)
	{
		mCurrentProject->Do(what, who);
	}
}



void MainFrameImpl::OnAUIWindowEvent( AUIWindowEvent& event )
{
	wxWindow* wnd = event.GetWindow();
	wxAuiPaneInfo& pane = m_mgr.GetPane(wnd);

	switch (event.GetCommand())
	{
		case AUIWindowEvent::AddWindow:
			AddPane( wnd, event.GetName(), event.DoUpdate() );
		break;

		case AUIWindowEvent::RemoveWindow:
			if (wnd)
			{
				m_mgr.DetachPane( wnd );
			}
		break;

		case AUIWindowEvent::UpdateManager:
			mProjectWindow->UpdateProjectTree();
			UpdateMenuStates();
		break;
		
		case AUIWindowEvent::RenameWindow:
			pane.Caption( event.GetName() );
		break;

		case AUIWindowEvent::ShowWindow:
			pane.Show( true );
		break;

		case AUIWindowEvent::HideWindow:
			pane.Show( false );
		break;


		case AUIWindowEvent::SetActive:
			wnd->SetFocus();
		break;
	}

	if (event.DoUpdate())
	{
		m_mgr.Update();
	}
}



void MainFrameImpl::OnEditorRebuildDataEvent( EditorRebuildDataEvent& event )
{
	switch (event.GetWhat())
	{
		case EditorRebuildDataEvent::whEditorStateChanged:
			UpdateMenuStates();
			mProjectWindow->UpdateState( event.GetEditor() );
		break;
	}

	event.Skip();
}



void MainFrameImpl::OnAUIManagerEvent( wxAuiManagerEvent& event )
{
	mCurrentPane = event.GetPane();

	if (!mCurrentProject || !mCurrentProject->FindEditor( mCurrentPane->window ))
	{
		mCurrentPane = NULL;
	}
	
	
	event.Skip();
}



/* virtual */ void MainFrameImpl::OnPaneClose( wxAuiManagerEvent& event ) 
{ 
	wxAuiPaneInfo* pane = event.GetPane();

	UpdateViewMenu( pane->window->GetId(), !pane->IsShown() );

	event.Skip(); 
}