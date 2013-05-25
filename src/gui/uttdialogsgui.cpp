///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include "uttdialogsgui.h"

///////////////////////////////////////////////////////////////////////////

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

AboutBoxGui::AboutBoxGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxGridSizer* gSizer14;
	gSizer14 = new wxGridSizer( 1, 1, 0, 0 );
	
	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer13->AddGrowableCol( 0 );
	fgSizer13->AddGrowableRow( 0 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer15;
	fgSizer15 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer15->SetFlexibleDirection( wxBOTH );
	fgSizer15->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer13->Add( fgSizer15, 1, wxEXPAND, 5 );
	
	mCloseButton = new wxButton( m_panel3, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer13->Add( mCloseButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	m_panel3->SetSizer( fgSizer13 );
	m_panel3->Layout();
	fgSizer13->Fit( m_panel3 );
	gSizer14->Add( m_panel3, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( gSizer14 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

AboutBoxGui::~AboutBoxGui()
{
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

CreateProjectGui::CreateProjectGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 1, 1, 0, 0 );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 5, 2, 0, 0 );
	fgSizer4->AddGrowableCol( 1 );
	fgSizer4->AddGrowableRow( 4 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Filename:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer4->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );
	
	mFileDlg = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a project filename and location"), wxT("*.UTTPROJ"), wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL );
	fgSizer4->Add( mFileDlg, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("Game directory:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer4->Add( m_staticText11, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );
	
	mDirDlg = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a game folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE|wxDIRP_DIR_MUST_EXIST );
	fgSizer4->Add( mDirDlg, 1, wxTOP|wxBOTTOM|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Default module:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer4->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );
	
	mModulesCombo = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY ); 
	fgSizer4->Add( mModulesCombo, 1, wxTOP|wxBOTTOM|wxEXPAND, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Default version:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer4->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5 );
	
	mVersionsCombo = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY ); 
	fgSizer4->Add( mVersionsCombo, 1, wxTOP|wxBOTTOM|wxEXPAND, 5 );
	
	
	fgSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	fgSizer4->Add( m_sdbSizer1, 0, wxALIGN_BOTTOM|wxALIGN_RIGHT, 5 );
	
	
	gSizer4->Add( fgSizer4, 1, wxEXPAND|wxALL, 5 );
	
	
	this->SetSizer( gSizer4 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	mFileDlg->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( CreateProjectGui::OnProjectFileNameChanged ), NULL, this );
	mModulesCombo->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( CreateProjectGui::OnModuleChanged ), NULL, this );
	m_sdbSizer1OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CreateProjectGui::OnOKButtonClick ), NULL, this );
}

CreateProjectGui::~CreateProjectGui()
{
	// Disconnect Events
	mFileDlg->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( CreateProjectGui::OnProjectFileNameChanged ), NULL, this );
	mModulesCombo->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( CreateProjectGui::OnModuleChanged ), NULL, this );
	m_sdbSizer1OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CreateProjectGui::OnOKButtonClick ), NULL, this );
	
}
