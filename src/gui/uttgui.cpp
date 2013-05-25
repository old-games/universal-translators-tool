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
