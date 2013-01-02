///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include "uttgui.h"

///////////////////////////////////////////////////////////////////////////

UttMainFrame::UttMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 640,480 ), wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_ALLOW_ACTIVE_PANE|wxAUI_MGR_ALLOW_FLOATING|wxAUI_MGR_LIVE_RESIZE|wxAUI_MGR_TRANSPARENT_DRAG|wxAUI_MGR_TRANSPARENT_HINT);
	
	mMainMenu = new wxMenuBar( 0 );
	mFileMenu = new wxMenu();
	wxMenuItem* mFileNew;
	mFileNew = new wxMenuItem( mFileMenu, wxID_NEW_PROJECT, wxString( wxT("New project") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mFileNew->SetBitmaps( wxArtProvider::GetBitmap( wxART_NEW_DIR, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mFileNew->SetBitmap( wxArtProvider::GetBitmap( wxART_NEW_DIR, wxART_MENU ) );
	#endif
	mFileMenu->Append( mFileNew );
	
	mFileMenu->AppendSeparator();
	
	wxMenuItem* mFileOpen;
	mFileOpen = new wxMenuItem( mFileMenu, wxID_OPEN_PROJECT, wxString( wxT("Open project") ) + wxT('\t') + wxT("CTRL-O"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mFileOpen->SetBitmaps( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mFileOpen->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_MENU ) );
	#endif
	mFileMenu->Append( mFileOpen );
	
	wxMenuItem* mFileSave;
	mFileSave = new wxMenuItem( mFileMenu, wxID_SAVE_PROJECT, wxString( wxT("Save project") ) + wxT('\t') + wxT("CTRL-S"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mFileSave->SetBitmaps( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mFileSave->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_MENU ) );
	#endif
	mFileMenu->Append( mFileSave );
	
	wxMenuItem* mFileSaveAs;
	mFileSaveAs = new wxMenuItem( mFileMenu, wxID_SAVE_PROJECT_AS, wxString( wxT("Save project as...") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mFileSaveAs->SetBitmaps( wxArtProvider::GetBitmap( wxART_FILE_SAVE_AS, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mFileSaveAs->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_SAVE_AS, wxART_MENU ) );
	#endif
	mFileMenu->Append( mFileSaveAs );
	
	mFileMenu->AppendSeparator();
	
	wxMenuItem* mFileClose;
	mFileClose = new wxMenuItem( mFileMenu, wxID_CLOSE_PROJECT, wxString( wxT("Close project") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mFileClose->SetBitmaps( wxArtProvider::GetBitmap( wxART_REMOVABLE, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mFileClose->SetBitmap( wxArtProvider::GetBitmap( wxART_REMOVABLE, wxART_MENU ) );
	#endif
	mFileMenu->Append( mFileClose );
	
	mFileMenu->AppendSeparator();
	
	wxMenuItem* mFileQuit;
	mFileQuit = new wxMenuItem( mFileMenu, wxID_FILE_QUIT, wxString( wxT("Quit") ) + wxT('\t') + wxT("ALT-F4"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mFileQuit->SetBitmaps( wxArtProvider::GetBitmap( wxART_QUIT, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mFileQuit->SetBitmap( wxArtProvider::GetBitmap( wxART_QUIT, wxART_MENU ) );
	#endif
	mFileMenu->Append( mFileQuit );
	
	mMainMenu->Append( mFileMenu, wxT("File") ); 
	
	mImportExportMenu = new wxMenu();
	wxMenuItem* mIE_ImpFont;
	mIE_ImpFont = new wxMenuItem( mImportExportMenu, wxID_IMPORT_FONT, wxString( wxT("Import font") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mIE_ImpFont->SetBitmaps( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mIE_ImpFont->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_MENU ) );
	#endif
	mImportExportMenu->Append( mIE_ImpFont );
	
	wxMenuItem* mIE_ImpImage;
	mIE_ImpImage = new wxMenuItem( mImportExportMenu, wxID_IMPORT_IMAGE, wxString( wxT("Import image") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mIE_ImpImage->SetBitmaps( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mIE_ImpImage->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_MENU ) );
	#endif
	mImportExportMenu->Append( mIE_ImpImage );
	
	wxMenuItem* mIE_ImpLibrary;
	mIE_ImpLibrary = new wxMenuItem( mImportExportMenu, wxID_IMPORT_LIBRARY, wxString( wxT("Import library") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mIE_ImpLibrary->SetBitmaps( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mIE_ImpLibrary->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_MENU ) );
	#endif
	mImportExportMenu->Append( mIE_ImpLibrary );
	
	wxMenuItem* mIE_ImpAnimation;
	mIE_ImpAnimation = new wxMenuItem( mImportExportMenu, wxID_IMPORT_ANIMATION, wxString( wxT("Import animation") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mIE_ImpAnimation->SetBitmaps( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mIE_ImpAnimation->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_MENU ) );
	#endif
	mImportExportMenu->Append( mIE_ImpAnimation );
	
	mImportExportMenu->AppendSeparator();
	
	wxMenuItem* mIE_ExpFont;
	mIE_ExpFont = new wxMenuItem( mImportExportMenu, wxID_EXPORT_FONT, wxString( wxT("Export font") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mIE_ExpFont->SetBitmaps( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mIE_ExpFont->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_MENU ) );
	#endif
	mImportExportMenu->Append( mIE_ExpFont );
	
	wxMenuItem* mIE_ExpImage;
	mIE_ExpImage = new wxMenuItem( mImportExportMenu, wxID_EXPORT_IMAGE, wxString( wxT("Export image") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mIE_ExpImage->SetBitmaps( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mIE_ExpImage->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_MENU ) );
	#endif
	mImportExportMenu->Append( mIE_ExpImage );
	
	wxMenuItem* mIE_ExpLibrary;
	mIE_ExpLibrary = new wxMenuItem( mImportExportMenu, wxID_EXPORT_LIBRARY, wxString( wxT("Export library") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mIE_ExpLibrary->SetBitmaps( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mIE_ExpLibrary->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_MENU ) );
	#endif
	mImportExportMenu->Append( mIE_ExpLibrary );
	
	wxMenuItem* mIE_ExpAnimation;
	mIE_ExpAnimation = new wxMenuItem( mImportExportMenu, wxID_EXPORT_ANIMATION, wxString( wxT("Export animation") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mIE_ExpAnimation->SetBitmaps( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mIE_ExpAnimation->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_MENU ) );
	#endif
	mImportExportMenu->Append( mIE_ExpAnimation );
	
	mMainMenu->Append( mImportExportMenu, wxT("Import/Export") ); 
	
	mEditMenu = new wxMenu();
	wxMenuItem* mEditUndo;
	mEditUndo = new wxMenuItem( mEditMenu, wxID_UNDO, wxString( wxT("Undo") ) + wxT('\t') + wxT("CTRL-Z"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mEditUndo->SetBitmaps( wxArtProvider::GetBitmap( wxART_UNDO, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mEditUndo->SetBitmap( wxArtProvider::GetBitmap( wxART_UNDO, wxART_MENU ) );
	#endif
	mEditMenu->Append( mEditUndo );
	
	wxMenuItem* mEditRedo;
	mEditRedo = new wxMenuItem( mEditMenu, wxID_REDO, wxString( wxT("Redo") ) + wxT('\t') + wxT("CTRL-Y"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mEditRedo->SetBitmaps( wxArtProvider::GetBitmap( wxART_REDO, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mEditRedo->SetBitmap( wxArtProvider::GetBitmap( wxART_REDO, wxART_MENU ) );
	#endif
	mEditMenu->Append( mEditRedo );
	
	mMainMenu->Append( mEditMenu, wxT("Edit") ); 
	
	mViewMenu = new wxMenu();
	wxMenuItem* mViewToolBar;
	mViewToolBar = new wxMenuItem( mViewMenu, wxID_VIEW_TOOLBAR, wxString( wxT("Toolbar") ) + wxT('\t') + wxT("CTRL-T"), wxT("Show/hide main toolbar"), wxITEM_CHECK );
	#ifdef __WXMSW__
	mViewToolBar->SetBitmaps( wxNullBitmap );
	#elif defined( __WXGTK__ )
	mViewToolBar->SetBitmap( wxNullBitmap );
	#endif
	mViewMenu->Append( mViewToolBar );
	mViewToolBar->Check( true );
	
	wxMenuItem* mViewProject;
	mViewProject = new wxMenuItem( mViewMenu, wxID_VIEW_PROJECT, wxString( wxT("Project window") ) + wxT('\t') + wxT("CTRL-P"), wxT("Show/hide project window"), wxITEM_CHECK );
	#ifdef __WXMSW__
	mViewProject->SetBitmaps( wxNullBitmap );
	#elif defined( __WXGTK__ )
	mViewProject->SetBitmap( wxNullBitmap );
	#endif
	mViewMenu->Append( mViewProject );
	mViewProject->Check( true );
	
	wxMenuItem* mViewLog;
	mViewLog = new wxMenuItem( mViewMenu, wxID_VIEW_LOG, wxString( wxT("Log window") ) + wxT('\t') + wxT("CTRL-L"), wxT("Show/hide log window"), wxITEM_CHECK );
	#ifdef __WXMSW__
	mViewLog->SetBitmaps( wxNullBitmap );
	#elif defined( __WXGTK__ )
	mViewLog->SetBitmap( wxNullBitmap );
	#endif
	mViewMenu->Append( mViewLog );
	mViewLog->Check( true );
	
	mMainMenu->Append( mViewMenu, wxT("View") ); 
	
	mLuaMenu = new wxMenu();
	wxMenuItem* mLuaSelect;
	mLuaSelect = new wxMenuItem( mLuaMenu, wxID_LUA_SELECT, wxString( wxT("Select module") ) + wxT('\t') + wxT("ALT-M"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mLuaSelect->SetBitmaps( wxArtProvider::GetBitmap( wxART_EXECUTABLE_FILE, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mLuaSelect->SetBitmap( wxArtProvider::GetBitmap( wxART_EXECUTABLE_FILE, wxART_MENU ) );
	#endif
	mLuaMenu->Append( mLuaSelect );
	
	wxMenuItem* mLuaSelect1;
	mLuaSelect1 = new wxMenuItem( mLuaMenu, wxID_LUA_VERSION, wxString( wxT("Select version") ) + wxT('\t') + wxT("ALT-V"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mLuaSelect1->SetBitmaps( wxArtProvider::GetBitmap( wxART_LIST_VIEW, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mLuaSelect1->SetBitmap( wxArtProvider::GetBitmap( wxART_LIST_VIEW, wxART_MENU ) );
	#endif
	mLuaMenu->Append( mLuaSelect1 );
	
	mLuaMenu->AppendSeparator();
	
	wxMenuItem* mLuaReboot;
	mLuaReboot = new wxMenuItem( mLuaMenu, wxID_LUA_REBOOT, wxString( wxT("Reboot scripts") ) + wxT('\t') + wxT("CTRL-R"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mLuaReboot->SetBitmaps( wxArtProvider::GetBitmap( wxART_HARDDISK, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mLuaReboot->SetBitmap( wxArtProvider::GetBitmap( wxART_HARDDISK, wxART_MENU ) );
	#endif
	mLuaMenu->Append( mLuaReboot );
	
	mMainMenu->Append( mLuaMenu, wxT("Lua") ); 
	
	mModuleMenu = new wxMenu();
	mMainMenu->Append( mModuleMenu, wxT("Module") ); 
	
	mHelpMenu = new wxMenu();
	wxMenuItem* mHelpHelp;
	mHelpHelp = new wxMenuItem( mHelpMenu, wxID_HELP_HELP, wxString( wxT("Help") ) + wxT('\t') + wxT("F1"), wxT("Documentation "), wxITEM_NORMAL );
	#ifdef __WXMSW__
	mHelpHelp->SetBitmaps( wxArtProvider::GetBitmap( wxART_HELP_BOOK, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mHelpHelp->SetBitmap( wxArtProvider::GetBitmap( wxART_HELP_BOOK, wxART_MENU ) );
	#endif
	mHelpMenu->Append( mHelpHelp );
	
	wxMenuItem* mHelpAbout;
	mHelpAbout = new wxMenuItem( mHelpMenu, wxID_HELP_ABOUT, wxString( wxT("About...") ) , wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mHelpAbout->SetBitmaps( wxArtProvider::GetBitmap( wxART_HELP, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mHelpAbout->SetBitmap( wxArtProvider::GetBitmap( wxART_HELP, wxART_MENU ) );
	#endif
	mHelpMenu->Append( mHelpAbout );
	
	mMainMenu->Append( mHelpMenu, wxT("Help") ); 
	
	this->SetMenuBar( mMainMenu );
	
	mMainToolBar = new wxAuiToolBar( this, wxID_VIEW_TOOLBAR, wxDefaultPosition, wxDefaultSize, wxAUI_TB_GRIPPER|wxAUI_TB_HORZ_LAYOUT|wxAUI_TB_OVERFLOW );
	mMainToolBar->SetToolSeparation( 4 );
	mMainToolBar->SetToolPacking( 2 );
	mMainToolBar->AddTool( wxID_NEW_PROJECT, wxT("New project"), wxArtProvider::GetBitmap( wxART_NEW_DIR, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxT("New project"), wxEmptyString, NULL ); 
	
	mMainToolBar->AddSeparator(); 
	
	mMainToolBar->AddTool( wxID_OPEN_PROJECT, wxT("Open project"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxT("Open project"), wxEmptyString, NULL ); 
	
	mMainToolBar->AddTool( wxID_SAVE_PROJECT, wxT("Save project"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxT("Save project"), wxEmptyString, NULL ); 
	
	mMainToolBar->AddSeparator(); 
	
	mMainToolBar->AddTool( wxID_IMPORT_FONT, wxT("Import font"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxT("Import font"), wxEmptyString, NULL ); 
	
	mMainToolBar->AddTool( wxID_IMPORT_IMAGE, wxT("Import image"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxT("Import image"), wxEmptyString, NULL ); 
	
	mMainToolBar->AddTool( wxID_IMPORT_LIBRARY, wxT("Import library"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxT("Import library"), wxEmptyString, NULL ); 
	
	mMainToolBar->AddTool( wxID_IMPORT_ANIMATION, wxT("Import animation"), wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxT("Import animation"), wxEmptyString, NULL ); 
	
	mMainToolBar->AddSeparator(); 
	
	mMainToolBar->AddTool( wxID_EXPORT_FONT, wxT("Export font"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxT("Export font"), wxEmptyString, NULL ); 
	
	mMainToolBar->AddTool( wxID_EXPORT_IMAGE, wxT("Export image"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxT("Export image"), wxEmptyString, NULL ); 
	
	mMainToolBar->AddTool( wxID_EXPORT_LIBRARY, wxT("Export library"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxT("Export library"), wxEmptyString, NULL ); 
	
	mMainToolBar->AddTool( wxID_EXPORT_ANIMATION, wxT("Export animation"), wxArtProvider::GetBitmap( wxART_FILE_SAVE, wxART_TOOLBAR ), wxNullBitmap, wxITEM_NORMAL, wxT("Export animation"), wxEmptyString, NULL ); 
	
	mMainToolBar->Realize();
	m_mgr.AddPane( mMainToolBar, wxAuiPaneInfo().Name( wxT("MainToolbar") ).Top().CaptionVisible( false ).PinButton( true ).PaneBorder( false ).Gripper().Dock().Fixed().DockFixed( false ).Row( 1 ).Layer( 10 ).ToolbarPane() );
	
	mProjectWindow = new ProjectWindow( this, wxID_VIEW_PROJECT );
	m_mgr.AddPane( mProjectWindow, wxAuiPaneInfo() .Name( wxT("ProjectWindow") ).Left() .Caption( wxT("No active project") ).MaximizeButton( true ).MinimizeButton( true ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).Layer( 1 ).DefaultPane() );
	
	mLogWindow = new LogWindowImpl( this, wxID_VIEW_LOG );
	m_mgr.AddPane( mLogWindow, wxAuiPaneInfo() .Name( wxT("LogWindow") ).Left() .Caption( wxT("Log") ).MaximizeButton( true ).MinimizeButton( true ).PinButton( true ).Dock().Resizable().FloatingSize( wxSize( 37,134 ) ).Layer( 1 ) );
	
	mStatusBar = this->CreateStatusBar( 3, wxST_SIZEGRIP, wxID_ANY );
	
	m_mgr.Update();
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_AUI_PANE_CLOSE, wxAuiManagerEventHandler( UttMainFrame::OnPaneClose ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( UttMainFrame::OnClose ) );
	this->Connect( mFileNew->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mFileOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mFileSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mFileSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mFileClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mIE_ImpFont->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mIE_ImpImage->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mIE_ImpLibrary->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mIE_ImpAnimation->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mIE_ExpFont->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mIE_ExpImage->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mIE_ExpLibrary->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mIE_ExpAnimation->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mEditUndo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mEditRedo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mViewToolBar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mViewProject->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mViewLog->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mLuaSelect->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mLuaSelect1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mLuaReboot->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mHelpHelp->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( wxID_NEW_PROJECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( wxID_OPEN_PROJECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( wxID_SAVE_PROJECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( wxID_IMPORT_FONT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( wxID_IMPORT_IMAGE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( wxID_IMPORT_LIBRARY, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( wxID_IMPORT_ANIMATION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( wxID_EXPORT_FONT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( wxID_EXPORT_IMAGE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( wxID_EXPORT_LIBRARY, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( wxID_EXPORT_ANIMATION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
}

UttMainFrame::~UttMainFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_AUI_PANE_CLOSE, wxAuiManagerEventHandler( UttMainFrame::OnPaneClose ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( UttMainFrame::OnClose ) );
	this->Disconnect( wxID_NEW_PROJECT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_OPEN_PROJECT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_SAVE_PROJECT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_SAVE_PROJECT_AS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_CLOSE_PROJECT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_FILE_QUIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_IMPORT_FONT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_IMPORT_IMAGE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_IMPORT_LIBRARY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_IMPORT_ANIMATION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_EXPORT_FONT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_EXPORT_IMAGE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_EXPORT_LIBRARY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_EXPORT_ANIMATION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_UNDO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_REDO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_VIEW_TOOLBAR, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_VIEW_PROJECT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_VIEW_LOG, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_LUA_SELECT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_LUA_VERSION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_LUA_REBOOT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_HELP_HELP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_HELP_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_NEW_PROJECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_OPEN_PROJECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_SAVE_PROJECT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_IMPORT_FONT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_IMPORT_IMAGE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_IMPORT_LIBRARY, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_IMPORT_ANIMATION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_EXPORT_FONT, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_EXPORT_IMAGE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_EXPORT_LIBRARY, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_EXPORT_ANIMATION, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	
	m_mgr.UnInit();
	
}

FontSettingsGui::FontSettingsGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 1, 1, 0, 0 );
	
	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 10, 2, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->AddGrowableRow( 9 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Total symbols:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer3->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mNumSpinCtrl = new wxSpinCtrl( m_scrolledWindow1, wxID_NUM_SPIN_CTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 2048, 130 );
	fgSizer3->Add( mNumSpinCtrl, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Codes:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer3->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mSetCodesBtn = new wxButton( m_scrolledWindow1, wxID_SET_CODES_BTN, wxT("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	fgSizer3->Add( mSetCodesBtn, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText5 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Max width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer3->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mMaxWidthSpinCtrl = new wxSpinCtrl( m_scrolledWindow1, wxID_MAX_WIDTH_SPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer3->Add( mMaxWidthSpinCtrl, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText3 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Max height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer3->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mMaxHeightSpinCtrl = new wxSpinCtrl( m_scrolledWindow1, wxID_MAX_HEIGHT_SPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer3->Add( mMaxHeightSpinCtrl, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText6 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Min width:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer3->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mMinWidthSpinCtrl = new wxSpinCtrl( m_scrolledWindow1, wxID_MIN_WIDTH_SPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer3->Add( mMinWidthSpinCtrl, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText4 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Min height:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer3->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mMinHeightSpinCtrl = new wxSpinCtrl( m_scrolledWindow1, wxID_MIN_HEIGHT_SPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer3->Add( mMinHeightSpinCtrl, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText8 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Base line:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer3->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mBaseLineSpinCtrl = new wxSpinCtrl( m_scrolledWindow1, wxID_BASE_LINE_SPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer3->Add( mBaseLineSpinCtrl, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText9 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Capitals line:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer3->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mCapLineSpinCtrl = new wxSpinCtrl( m_scrolledWindow1, wxID_CAP_LINE_SPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer3->Add( mCapLineSpinCtrl, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText10 = new wxStaticText( m_scrolledWindow1, wxID_ANY, wxT("Lower line"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer3->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mLowLineSpinCtrl = new wxSpinCtrl( m_scrolledWindow1, wxID_LOW_LINE_SPIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 10, 0 );
	fgSizer3->Add( mLowLineSpinCtrl, 0, wxALL|wxEXPAND, 5 );
	
	mOkBtn = new wxButton( m_scrolledWindow1, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( mOkBtn, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	mCancelBtn = new wxButton( m_scrolledWindow1, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( mCancelBtn, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxRIGHT|wxLEFT, 5 );
	
	
	m_scrolledWindow1->SetSizer( fgSizer3 );
	m_scrolledWindow1->Layout();
	fgSizer3->Fit( m_scrolledWindow1 );
	gSizer3->Add( m_scrolledWindow1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( gSizer3 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	mNumSpinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mSetCodesBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontSettingsGui::OnBtnClick ), NULL, this );
	mMaxWidthSpinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mMaxHeightSpinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mMinWidthSpinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mMinHeightSpinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mBaseLineSpinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mCapLineSpinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mLowLineSpinCtrl->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
}

FontSettingsGui::~FontSettingsGui()
{
	// Disconnect Events
	mNumSpinCtrl->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mSetCodesBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontSettingsGui::OnBtnClick ), NULL, this );
	mMaxWidthSpinCtrl->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mMaxHeightSpinCtrl->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mMinWidthSpinCtrl->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mMinHeightSpinCtrl->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mBaseLineSpinCtrl->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mCapLineSpinCtrl->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	mLowLineSpinCtrl->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FontSettingsGui::OnSpinCtrl ), NULL, this );
	
}

LetterCodesGui::LetterCodesGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 500,500 ), wxDefaultSize );
	
	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 1, 1, 0, 0 );
	
	m_scrolledWindow2 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow2->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 3, 1, 0, 0 );
	fgSizer4->AddGrowableCol( 0 );
	fgSizer4->AddGrowableRow( 2 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mAutoSizer = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow2, wxID_ANY, wxT("Auto:") ), wxHORIZONTAL );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer5->AddGrowableCol( 3 );
	fgSizer5->AddGrowableRow( 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText11 = new wxStaticText( m_scrolledWindow2, wxID_ANY, wxT("Initial:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer5->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mInitialSpinCtrl = new wxSpinCtrl( m_scrolledWindow2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 2048, 32 );
	fgSizer5->Add( mInitialSpinCtrl, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mGenerateBtn = new wxButton( m_scrolledWindow2, wxID_GENERATE_CODES_BTN, wxT("Generate..."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( mGenerateBtn, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText111 = new wxStaticText( m_scrolledWindow2, wxID_ANY, wxT("Codepage:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	fgSizer5->Add( m_staticText111, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	mCodeTxt = new wxTextCtrl( m_scrolledWindow2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	mCodeTxt->SetMaxLength( 0 ); 
	fgSizer5->Add( mCodeTxt, 0, wxALL, 5 );
	
	mGetEncodingBtn = new wxButton( m_scrolledWindow2, wxID_GET_ENCODING_BTN, wxT("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	fgSizer5->Add( mGetEncodingBtn, 0, wxALL, 5 );
	
	
	mAutoSizer->Add( fgSizer5, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer4->Add( mAutoSizer, 1, wxEXPAND, 5 );
	
	mBtnsSizer = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow2, wxID_ANY, wxT("Controls:") ), wxHORIZONTAL );
	
	wxGridSizer* gSizer5;
	gSizer5 = new wxGridSizer( 1, 2, 0, 0 );
	
	mOkBtn = new wxButton( m_scrolledWindow2, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer5->Add( mOkBtn, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mCancelBtn = new wxButton( m_scrolledWindow2, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer5->Add( mCancelBtn, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	mBtnsSizer->Add( gSizer5, 1, wxEXPAND, 5 );
	
	
	fgSizer4->Add( mBtnsSizer, 1, wxEXPAND, 5 );
	
	mGridSizer = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow2, wxID_ANY, wxT("Letters:") ), wxVERTICAL );
	
	mCodesGrid = new wxGrid( m_scrolledWindow2, wxID_CODES_GRID, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	mCodesGrid->CreateGrid( 0, 0 );
	mCodesGrid->EnableEditing( true );
	mCodesGrid->EnableGridLines( true );
	mCodesGrid->EnableDragGridSize( false );
	mCodesGrid->SetMargins( 0, 0 );
	
	// Columns
	mCodesGrid->EnableDragColMove( false );
	mCodesGrid->EnableDragColSize( true );
	mCodesGrid->SetColLabelSize( 30 );
	mCodesGrid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	mCodesGrid->EnableDragRowSize( true );
	mCodesGrid->SetRowLabelSize( 80 );
	mCodesGrid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	mCodesGrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	mGridSizer->Add( mCodesGrid, 1, wxALL|wxEXPAND, 5 );
	
	
	fgSizer4->Add( mGridSizer, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	
	m_scrolledWindow2->SetSizer( fgSizer4 );
	m_scrolledWindow2->Layout();
	fgSizer4->Fit( m_scrolledWindow2 );
	gSizer4->Add( m_scrolledWindow2, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( gSizer4 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( LetterCodesGui::OnSize ) );
	mGenerateBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LetterCodesGui::OnBtnClick ), NULL, this );
	mGetEncodingBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LetterCodesGui::OnBtnClick ), NULL, this );
	mOkBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LetterCodesGui::OnBtnClick ), NULL, this );
}

LetterCodesGui::~LetterCodesGui()
{
	// Disconnect Events
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( LetterCodesGui::OnSize ) );
	mGenerateBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LetterCodesGui::OnBtnClick ), NULL, this );
	mGetEncodingBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LetterCodesGui::OnBtnClick ), NULL, this );
	mOkBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LetterCodesGui::OnBtnClick ), NULL, this );
	
}

FontEditGui::FontEditGui( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetMinSize( wxSize( 400,300 ) );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 1, 1, 0, 0 );
	
	mFontScrolledBack = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL );
	mFontScrolledBack->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableRow( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( mFontScrolledBack, wxID_ANY, wxT("Controls:") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 1, 4, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->AddGrowableCol( 2 );
	fgSizer2->AddGrowableRow( 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mCreateBtn = new wxButton( mFontScrolledBack, wxID_CREATE_FONT, wxT("Create new..."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( mCreateBtn, 0, wxALL, 5 );
	
	mSaveBtn = new wxButton( mFontScrolledBack, wxID_SAVE_BTN, wxT("Save..."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( mSaveBtn, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	mLoadBtn = new wxButton( mFontScrolledBack, wxID_LOAD_BTN, wxT("Load..."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( mLoadBtn, 0, wxALL, 5 );
	
	mSettingsBtn = new wxButton( mFontScrolledBack, wxID_FONT_SETTINGS, wxT("Font settings..."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( mSettingsBtn, 0, wxALL, 5 );
	
	
	sbSizer4->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	
	fgSizer1->Add( sbSizer4, 1, wxEXPAND, 5 );
	
	wxGridSizer* gSizer11;
	gSizer11 = new wxGridSizer( 1, 1, 0, 0 );
	
	mFontSplitter = new wxSplitterWindow( mFontScrolledBack, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3DBORDER|wxSP_3DSASH|wxSP_LIVE_UPDATE|wxSP_NO_XP_THEME|wxFULL_REPAINT_ON_RESIZE );
	mFontSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( FontEditGui::mFontSplitterOnIdle ), NULL, this );
	mFontSplitter->SetMinimumPaneSize( 64 );
	
	mRibbonOwner = new wxPanel( mFontSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE|wxTAB_TRAVERSAL );
	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( mRibbonOwner, wxID_ANY, wxT("Symbols:") ), wxVERTICAL );
	
	sbSizer11->SetMinSize( wxSize( 256,128 ) ); 
	mSymbolsRibbon = new BitmapRibbonCtrl( mRibbonOwner );
	sbSizer11->Add( mSymbolsRibbon, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	mRibbonOwner->SetSizer( sbSizer11 );
	mRibbonOwner->Layout();
	sbSizer11->Fit( mRibbonOwner );
	mSymEditorOwner = new wxPanel( mFontSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	mSymEditorOwner->SetMinSize( wxSize( -1,200 ) );
	
	mCentralSizer = new wxGridSizer( 1, 1, 0, 0 );
	
	
	mSymEditorOwner->SetSizer( mCentralSizer );
	mSymEditorOwner->Layout();
	mCentralSizer->Fit( mSymEditorOwner );
	mFontSplitter->SplitHorizontally( mRibbonOwner, mSymEditorOwner, 64 );
	gSizer11->Add( mFontSplitter, 1, wxEXPAND, 5 );
	
	
	fgSizer1->Add( gSizer11, 1, wxEXPAND, 5 );
	
	
	mFontScrolledBack->SetSizer( fgSizer1 );
	mFontScrolledBack->Layout();
	fgSizer1->Fit( mFontScrolledBack );
	gSizer1->Add( mFontScrolledBack, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( gSizer1 );
	this->Layout();
	
	// Connect Events
	mCreateBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontEditGui::OnBtnClick ), NULL, this );
	mSaveBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontEditGui::OnBtnClick ), NULL, this );
	mLoadBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontEditGui::OnBtnClick ), NULL, this );
	mSettingsBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontEditGui::OnBtnClick ), NULL, this );
}

FontEditGui::~FontEditGui()
{
	// Disconnect Events
	mCreateBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontEditGui::OnBtnClick ), NULL, this );
	mSaveBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontEditGui::OnBtnClick ), NULL, this );
	mLoadBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontEditGui::OnBtnClick ), NULL, this );
	mSettingsBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontEditGui::OnBtnClick ), NULL, this );
	
}

EditPanelGui::EditPanelGui( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetMinSize( wxSize( 400,300 ) );
	
	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer( 1, 1, 0, 0 );
	
	mEditScrolledBack = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	mEditScrolledBack->SetScrollRate( 5, 5 );
	mEditSizer = new wxFlexGridSizer( 3, 1, 0, 0 );
	mEditSizer->AddGrowableCol( 0 );
	mEditSizer->AddGrowableRow( 0 );
	mEditSizer->SetFlexibleDirection( wxBOTH );
	mEditSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mDrawHolder = new wxStaticBoxSizer( new wxStaticBox( mEditScrolledBack, wxID_ANY, wxT("Image:") ), wxVERTICAL );
	
	
	mEditSizer->Add( mDrawHolder, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( mEditScrolledBack, wxID_ANY, wxT("Operations:") ), wxVERTICAL );
	
	wxGridSizer* gSizer8;
	gSizer8 = new wxGridSizer( 1, 1, 0, 0 );
	
	wxGridSizer* gSizer9;
	gSizer9 = new wxGridSizer( 1, 6, 0, 0 );
	
	mGridCheck = new wxCheckBox( mEditScrolledBack, wxID_GRID_CHECK, wxT("Enable grid"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer9->Add( mGridCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText12 = new wxStaticText( mEditScrolledBack, wxID_ANY, wxT("Gridmode:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	gSizer9->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	wxString mGridModeChoiceChoices[] = { wxT("Copy"), wxT("Xor") };
	int mGridModeChoiceNChoices = sizeof( mGridModeChoiceChoices ) / sizeof( wxString );
	mGridModeChoice = new wxChoice( mEditScrolledBack, wxID_GRID_MODE, wxDefaultPosition, wxDefaultSize, mGridModeChoiceNChoices, mGridModeChoiceChoices, 0 );
	mGridModeChoice->SetSelection( 0 );
	gSizer9->Add( mGridModeChoice, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mGetGridColour = new wxButton( mEditScrolledBack, wxID_GRIDCOL_BTN, wxT("Grid colour..."), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer9->Add( mGetGridColour, 0, wxALL, 5 );
	
	mSaveBtn = new wxButton( mEditScrolledBack, wxID_SAVE_BTN, wxT("Save..."), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer9->Add( mSaveBtn, 0, wxALIGN_RIGHT|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	mLoadBtn = new wxButton( mEditScrolledBack, wxID_LOAD_BTN, wxT("Load..."), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer9->Add( mLoadBtn, 0, wxTOP|wxBOTTOM|wxRIGHT, 5 );
	
	
	gSizer8->Add( gSizer9, 1, wxEXPAND, 5 );
	
	
	sbSizer10->Add( gSizer8, 1, wxEXPAND, 5 );
	
	
	mEditSizer->Add( sbSizer10, 1, wxEXPAND, 5 );
	
	mPalSizer = new wxGridSizer( 1, 1, 0, 0 );
	
	
	mEditSizer->Add( mPalSizer, 1, wxEXPAND, 5 );
	
	
	mEditScrolledBack->SetSizer( mEditSizer );
	mEditScrolledBack->Layout();
	mEditSizer->Fit( mEditScrolledBack );
	gSizer7->Add( mEditScrolledBack, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( gSizer7 );
	this->Layout();
	
	// Connect Events
	mGridCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	mGridModeChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	mGetGridColour->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	mSaveBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	mLoadBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
}

EditPanelGui::~EditPanelGui()
{
	// Disconnect Events
	mGridCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	mGridModeChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	mGetGridColour->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	mSaveBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	mLoadBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	
}

LibraryGui::LibraryGui( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxGridSizer* gSizer10;
	gSizer10 = new wxGridSizer( 1, 1, 0, 0 );
	
	mLibScrolledBack = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	mLibScrolledBack->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer7->AddGrowableCol( 0 );
	fgSizer7->AddGrowableRow( 0 );
	fgSizer7->SetFlexibleDirection( wxBOTH );
	fgSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mLibTree = new wxTreeCtrl( mLibScrolledBack, wxID_LIBTREE, wxDefaultPosition, wxDefaultSize, wxTR_FULL_ROW_HIGHLIGHT|wxTR_HAS_BUTTONS|wxTR_HAS_VARIABLE_ROW_HEIGHT|wxTR_HIDE_ROOT|wxTR_LINES_AT_ROOT|wxTR_MULTIPLE|wxTR_ROW_LINES );
	fgSizer7->Add( mLibTree, 1, wxALL|wxEXPAND, 5 );
	
	
	mLibScrolledBack->SetSizer( fgSizer7 );
	mLibScrolledBack->Layout();
	fgSizer7->Fit( mLibScrolledBack );
	gSizer10->Add( mLibScrolledBack, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( gSizer10 );
	this->Layout();
	
	// Connect Events
	mLibTree->Connect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( LibraryGui::OnTreeItemMenu ), NULL, this );
}

LibraryGui::~LibraryGui()
{
	// Disconnect Events
	mLibTree->Disconnect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( LibraryGui::OnTreeItemMenu ), NULL, this );
	
}
