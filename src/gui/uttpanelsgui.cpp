///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include "uttpanelsgui.h"

///////////////////////////////////////////////////////////////////////////

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
	
	mLibTree = new wxTreeListCtrl(mLibScrolledBack, wxID_LIBTREE, wxDefaultPosition, wxDefaultSize, wxTL_MULTIPLE);
	fgSizer7->Add( mLibTree, 1, wxALL|wxEXPAND, 5 );
	
	
	mLibScrolledBack->SetSizer( fgSizer7 );
	mLibScrolledBack->Layout();
	fgSizer7->Fit( mLibScrolledBack );
	gSizer10->Add( mLibScrolledBack, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( gSizer10 );
	this->Layout();
}

LibraryGui::~LibraryGui()
{
}
