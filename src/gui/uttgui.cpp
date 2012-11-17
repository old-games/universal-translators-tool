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
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);
	
	mMainMenu = new wxMenuBar( 0 );
	mFileMenu = new wxMenu();
	wxMenuItem* mFileOpen;
	mFileOpen = new wxMenuItem( mFileMenu, wxID_FILE_OPEN, wxString( wxT("Open") ) + wxT('\t') + wxT("F3"), wxEmptyString, wxITEM_NORMAL );
	#ifdef __WXMSW__
	mFileOpen->SetBitmaps( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_MENU ) );
	#elif defined( __WXGTK__ )
	mFileOpen->SetBitmap( wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_MENU ) );
	#endif
	mFileMenu->Append( mFileOpen );
	
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
	
	mAUINotebook = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_EXTERNAL_MOVE|wxAUI_NB_TAB_MOVE|wxAUI_NB_TAB_SPLIT|wxWANTS_CHARS );
	m_mgr.AddPane( mAUINotebook, wxAuiPaneInfo() .Center() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).CentrePane() );
	
	
	mLogWindow = new LogWindowImpl( this );
	m_mgr.AddPane( mLogWindow, wxAuiPaneInfo() .Bottom() .MaximizeButton( true ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ) );
	
	mStatusBar = this->CreateStatusBar( 3, wxST_SIZEGRIP, wxID_ANY );
	
	m_mgr.Update();
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( UttMainFrame::OnClose ) );
	this->Connect( mFileOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mFileQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mLuaSelect->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mLuaSelect1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mLuaReboot->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mHelpHelp->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Connect( mHelpAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
}

UttMainFrame::~UttMainFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( UttMainFrame::OnClose ) );
	this->Disconnect( wxID_FILE_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_FILE_QUIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_LUA_SELECT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_LUA_VERSION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_LUA_REBOOT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_HELP_HELP, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	this->Disconnect( wxID_HELP_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( UttMainFrame::OnMenuSelect ) );
	
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

SelectModuleGui::SelectModuleGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxStaticBoxSizer* mBoxSizer;
	mBoxSizer = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	mModulesChoice = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY ); 
	mBoxSizer->Add( mModulesChoice, 0, wxALL|wxEXPAND, 5 );
	
	wxGridSizer* gSizer6;
	gSizer6 = new wxGridSizer( 1, 2, 0, 0 );
	
	mOkBtn = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer6->Add( mOkBtn, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mCancelBtn = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer6->Add( mCancelBtn, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	mBoxSizer->Add( gSizer6, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( mBoxSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	mOkBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SelectModuleGui::OnBtnClick ), NULL, this );
}

SelectModuleGui::~SelectModuleGui()
{
	// Disconnect Events
	mOkBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SelectModuleGui::OnBtnClick ), NULL, this );
	
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
	fgSizer2 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 0 );
	fgSizer2->AddGrowableRow( 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mCreateBtn = new wxButton( mFontScrolledBack, wxID_CREATE_FONT, wxT("Create new..."), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( mCreateBtn, 0, wxALL, 5 );
	
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
	
	mCentralSizer = new wxStaticBoxSizer( new wxStaticBox( mSymEditorOwner, wxID_ANY, wxT("Editor:") ), wxVERTICAL );
	
	mCentralSizer->SetMinSize( wxSize( 256,128 ) ); 
	
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
	mSettingsBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontEditGui::OnBtnClick ), NULL, this );
}

FontEditGui::~FontEditGui()
{
	// Disconnect Events
	mCreateBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontEditGui::OnBtnClick ), NULL, this );
	mSettingsBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FontEditGui::OnBtnClick ), NULL, this );
	
}

EditPanelGui::EditPanelGui( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetMinSize( wxSize( 400,300 ) );
	
	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer( 1, 1, 0, 0 );
	
	mEditScrolledBack = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	mEditScrolledBack->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer6->AddGrowableCol( 0 );
	fgSizer6->AddGrowableRow( 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mDrawHolder = new wxStaticBoxSizer( new wxStaticBox( mEditScrolledBack, wxID_ANY, wxT("Image:") ), wxVERTICAL );
	
	
	fgSizer6->Add( mDrawHolder, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( mEditScrolledBack, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	wxGridSizer* gSizer8;
	gSizer8 = new wxGridSizer( 1, 1, 0, 0 );
	
	wxGridSizer* gSizer9;
	gSizer9 = new wxGridSizer( 1, 4, 0, 0 );
	
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
	
	
	gSizer8->Add( gSizer9, 1, wxEXPAND, 5 );
	
	
	sbSizer10->Add( gSizer8, 1, wxEXPAND, 5 );
	
	
	fgSizer6->Add( sbSizer10, 1, wxEXPAND, 5 );
	
	
	mEditScrolledBack->SetSizer( fgSizer6 );
	mEditScrolledBack->Layout();
	fgSizer6->Fit( mEditScrolledBack );
	gSizer7->Add( mEditScrolledBack, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( gSizer7 );
	this->Layout();
	
	// Connect Events
	mGridCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	mGridModeChoice->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	mGetGridColour->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
}

EditPanelGui::~EditPanelGui()
{
	// Disconnect Events
	mGridCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	mGridModeChoice->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	mGetGridColour->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditPanelGui::OnCommandEvent ), NULL, this );
	
}

PaletteWindowGui::PaletteWindowGui( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetMinSize( wxSize( 625,200 ) );
	
	wxGridSizer* gSizer10;
	gSizer10 = new wxGridSizer( 1, 1, 0, 0 );
	
	mPalScrolledBack = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	mPalScrolledBack->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer7->AddGrowableCol( 0 );
	fgSizer7->AddGrowableRow( 0 );
	fgSizer7->SetFlexibleDirection( wxBOTH );
	fgSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mPalHolder = new wxStaticBoxSizer( new wxStaticBox( mPalScrolledBack, wxID_ANY, wxT("Available colours:") ), wxVERTICAL );
	
	
	fgSizer7->Add( mPalHolder, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( mPalScrolledBack, wxID_ANY, wxT("Palette:") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 1, 1, 0, 0 );
	fgSizer8->AddGrowableCol( 0 );
	fgSizer8->AddGrowableRow( 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxGridSizer* gSizer13;
	gSizer13 = new wxGridSizer( 1, 2, 0, 0 );
	
	wxFlexGridSizer* fgSizer9;
	fgSizer9 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer9->SetFlexibleDirection( wxBOTH );
	fgSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText15 = new wxStaticText( mPalScrolledBack, wxID_ANY, wxT("Left R:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer9->Add( m_staticText15, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mLRSpin = new wxSpinCtrl( mPalScrolledBack, wxID_LR_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer9->Add( mLRSpin, 0, wxALL, 5 );
	
	m_staticText16 = new wxStaticText( mPalScrolledBack, wxID_ANY, wxT("G:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer9->Add( m_staticText16, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mLGSpin = new wxSpinCtrl( mPalScrolledBack, wxID_LG_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer9->Add( mLGSpin, 0, wxALL, 5 );
	
	m_staticText17 = new wxStaticText( mPalScrolledBack, wxID_ANY, wxT("B:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer9->Add( m_staticText17, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mLBSpin = new wxSpinCtrl( mPalScrolledBack, wxID_LB_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer9->Add( mLBSpin, 0, wxALL, 5 );
	
	
	gSizer13->Add( fgSizer9, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer11->AddGrowableCol( 0 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText18 = new wxStaticText( mPalScrolledBack, wxID_ANY, wxT("Right R:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer11->Add( m_staticText18, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	mRBSpin = new wxSpinCtrl( mPalScrolledBack, wxID_RB_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer11->Add( mRBSpin, 0, wxALL, 5 );
	
	m_staticText19 = new wxStaticText( mPalScrolledBack, wxID_ANY, wxT("G:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	fgSizer11->Add( m_staticText19, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRRSpin = new wxSpinCtrl( mPalScrolledBack, wxID_RR_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer11->Add( mRRSpin, 0, wxALL, 5 );
	
	m_staticText20 = new wxStaticText( mPalScrolledBack, wxID_ANY, wxT("B:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer11->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRGSpin = new wxSpinCtrl( mPalScrolledBack, wxID_RG_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer11->Add( mRGSpin, 0, wxALL, 5 );
	
	
	gSizer13->Add( fgSizer11, 1, wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer8->Add( gSizer13, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer12->Add( fgSizer8, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer111;
	fgSizer111 = new wxFlexGridSizer( 1, 7, 0, 0 );
	fgSizer111->AddGrowableCol( 4 );
	fgSizer111->AddGrowableRow( 0 );
	fgSizer111->SetFlexibleDirection( wxBOTH );
	fgSizer111->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText21 = new wxStaticText( mPalScrolledBack, wxID_ANY, wxT("Owner:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer111->Add( m_staticText21, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mOwnerType = new wxComboBox( mPalScrolledBack, wxID_OWNER_CHOICE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY ); 
	fgSizer111->Add( mOwnerType, 0, wxALL, 5 );
	
	m_staticText13 = new wxStaticText( mPalScrolledBack, wxID_ANY, wxT("Palette type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer111->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mPalType = new wxComboBox( mPalScrolledBack, wxID_PAL_CHOICE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY ); 
	fgSizer111->Add( mPalType, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	m_staticText14 = new wxStaticText( mPalScrolledBack, wxID_ANY, wxT("Set of CGA colours:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer111->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	mCGAType = new wxComboBox( mPalScrolledBack, wxID_CGA_CHOICE, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), 0, NULL, wxCB_READONLY ); 
	fgSizer111->Add( mCGAType, 0, wxALL, 5 );
	
	mCGAIntensity = new wxCheckBox( mPalScrolledBack, wxID_INTENSITY_CHECK, wxT("CGA intensity"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer111->Add( mCGAIntensity, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer12->Add( fgSizer111, 1, wxEXPAND, 5 );
	
	
	fgSizer7->Add( sbSizer12, 1, wxEXPAND, 5 );
	
	
	mPalScrolledBack->SetSizer( fgSizer7 );
	mPalScrolledBack->Layout();
	fgSizer7->Fit( mPalScrolledBack );
	gSizer10->Add( mPalScrolledBack, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( gSizer10 );
	this->Layout();
	
	// Connect Events
	mLRSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mLGSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mLBSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRBSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRRSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRGSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mOwnerType->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	mPalType->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	mCGAType->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	mCGAIntensity->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
}

PaletteWindowGui::~PaletteWindowGui()
{
	// Disconnect Events
	mLRSpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mLGSpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mLBSpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRBSpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRRSpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRGSpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mOwnerType->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	mPalType->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	mCGAType->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	mCGAIntensity->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	
}
