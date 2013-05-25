///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "pch.h"

#include "simplegui.h"

#include "../icon/to_left.xpm"
#include "../icon/to_right.xpm"

///////////////////////////////////////////////////////////////////////////

BitmapRibbonGui::BitmapRibbonGui( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxGridSizer* gSizer11;
	gSizer11 = new wxGridSizer( 1, 1, 0, 0 );
	
	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 1, 3, 0, 0 );
	fgSizer10->AddGrowableCol( 1 );
	fgSizer10->AddGrowableRow( 0 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	mScrollLeftBtn = new wxBitmapButton( this, wxID_SCROLLLEFT_BTN, wxBitmap( to_left_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer10->Add( mScrollLeftBtn, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mBitmapsHolder = new wxBoxSizer( wxHORIZONTAL );
	
	
	mBitmapsHolder->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer10->Add( mBitmapsHolder, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mScrollRightBtn = new wxBitmapButton( this, wxID_SCROLLRIGHT_BTN, wxBitmap( to_right_xpm ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	fgSizer10->Add( mScrollRightBtn, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	gSizer11->Add( fgSizer10, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	this->SetSizer( gSizer11 );
	this->Layout();
	
	// Connect Events
	mScrollLeftBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BitmapRibbonGui::OnButtonClick ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseDown ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( BitmapRibbonGui::OnMouseUp ), NULL, this );
	mScrollRightBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BitmapRibbonGui::OnButtonClick ), NULL, this );
	mScrollRightBtn->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseDown ), NULL, this );
	mScrollRightBtn->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( BitmapRibbonGui::OnMouseUp ), NULL, this );
}

BitmapRibbonGui::~BitmapRibbonGui()
{
	// Disconnect Events
	mScrollLeftBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BitmapRibbonGui::OnButtonClick ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseDown ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( BitmapRibbonGui::OnMouseUp ), NULL, this );
	mScrollRightBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BitmapRibbonGui::OnButtonClick ), NULL, this );
	mScrollRightBtn->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseDown ), NULL, this );
	mScrollRightBtn->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( BitmapRibbonGui::OnMouseUp ), NULL, this );
	
}

PaletteWindowGui::PaletteWindowGui( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetMinSize( wxSize( 800,300 ) );
	
	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer7->AddGrowableCol( 0 );
	fgSizer7->AddGrowableRow( 0 );
	fgSizer7->SetFlexibleDirection( wxBOTH );
	fgSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mPalHolder = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Available colours:") ), wxVERTICAL );
	
	
	fgSizer7->Add( mPalHolder, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Palette:") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer8->AddGrowableCol( 0 );
	fgSizer8->AddGrowableCol( 1 );
	fgSizer8->AddGrowableRow( 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer9;
	fgSizer9 = new wxFlexGridSizer( 1, 8, 0, 0 );
	fgSizer9->SetFlexibleDirection( wxBOTH );
	fgSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText15 = new wxStaticText( this, wxID_ANY, wxT("Left R:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer9->Add( m_staticText15, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mLRSpin = new wxSpinCtrl( this, wxID_LR_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer9->Add( mLRSpin, 0, wxALL, 5 );
	
	m_staticText16 = new wxStaticText( this, wxID_ANY, wxT("G:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer9->Add( m_staticText16, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mLGSpin = new wxSpinCtrl( this, wxID_LG_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer9->Add( mLGSpin, 0, wxALL, 5 );
	
	m_staticText17 = new wxStaticText( this, wxID_ANY, wxT("B:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer9->Add( m_staticText17, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mLBSpin = new wxSpinCtrl( this, wxID_LB_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer9->Add( mLBSpin, 0, wxALL, 5 );
	
	m_staticText22 = new wxStaticText( this, wxID_ANY, wxT("#"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	fgSizer9->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	mLISpin = new wxSpinCtrl( this, wxID_LI_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer9->Add( mLISpin, 0, wxALL, 5 );
	
	
	fgSizer8->Add( fgSizer9, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 1, 8, 0, 0 );
	fgSizer11->AddGrowableCol( 0 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText18 = new wxStaticText( this, wxID_ANY, wxT("Right R:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer11->Add( m_staticText18, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	mRBSpin = new wxSpinCtrl( this, wxID_RB_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer11->Add( mRBSpin, 0, wxALL, 5 );
	
	m_staticText19 = new wxStaticText( this, wxID_ANY, wxT("G:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	fgSizer11->Add( m_staticText19, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRRSpin = new wxSpinCtrl( this, wxID_RR_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer11->Add( mRRSpin, 0, wxALL, 5 );
	
	m_staticText20 = new wxStaticText( this, wxID_ANY, wxT("B:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer11->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRGSpin = new wxSpinCtrl( this, wxID_RG_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer11->Add( mRGSpin, 0, wxALL, 5 );
	
	m_staticText221 = new wxStaticText( this, wxID_ANY, wxT("#"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText221->Wrap( -1 );
	fgSizer11->Add( m_staticText221, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mRISpin = new wxSpinCtrl( this, wxID_RI_SPIN, wxEmptyString, wxDefaultPosition, wxSize( 60,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	fgSizer11->Add( mRISpin, 0, wxALL, 5 );
	
	
	fgSizer8->Add( fgSizer11, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	
	sbSizer12->Add( fgSizer8, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 1, 3, 0, 0 );
	fgSizer13->AddGrowableCol( 0 );
	fgSizer13->AddGrowableCol( 1 );
	fgSizer13->AddGrowableCol( 2 );
	fgSizer13->AddGrowableRow( 0 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer111;
	fgSizer111 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer111->SetFlexibleDirection( wxBOTH );
	fgSizer111->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mLockCheck = new wxCheckBox( this, wxID_PALLOCK_CHECK, wxT("Read only"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer111->Add( mLockCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	mHexCheck = new wxCheckBox( this, wxID_HEX_CHECK, wxT("Hex values"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer111->Add( mHexCheck, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	fgSizer13->Add( fgSizer111, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	wxFlexGridSizer* fgSizer112;
	fgSizer112 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer112->AddGrowableCol( 0 );
	fgSizer112->AddGrowableCol( 1 );
	fgSizer112->AddGrowableRow( 0 );
	fgSizer112->SetFlexibleDirection( wxBOTH );
	fgSizer112->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, wxT("Palette type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer112->Add( m_staticText13, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxALIGN_RIGHT, 5 );
	
	mPalType = new wxComboBox( this, wxID_PAL_CHOICE, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY ); 
	fgSizer112->Add( mPalType, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	
	fgSizer13->Add( fgSizer112, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 1, 3, 0, 0 );
	fgSizer12->AddGrowableCol( 0 );
	fgSizer12->AddGrowableCol( 1 );
	fgSizer12->AddGrowableCol( 2 );
	fgSizer12->AddGrowableRow( 0 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, wxT("Set of CGA colours:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer12->Add( m_staticText14, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxALIGN_RIGHT, 5 );
	
	mCGAType = new wxComboBox( this, wxID_CGA_CHOICE, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), 0, NULL, wxCB_READONLY ); 
	fgSizer12->Add( mCGAType, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );
	
	mCGAIntensity = new wxCheckBox( this, wxID_INTENSITY_CHECK, wxT("CGA intensity"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer12->Add( mCGAIntensity, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_RIGHT, 5 );
	
	
	fgSizer13->Add( fgSizer12, 1, wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	sbSizer12->Add( fgSizer13, 1, wxEXPAND, 5 );
	
	
	fgSizer7->Add( sbSizer12, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer7 );
	this->Layout();
	
	// Connect Events
	mLRSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mLGSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mLBSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mLISpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRBSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRRSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRGSpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRISpin->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mLockCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	mHexCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
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
	mLISpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRBSpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRRSpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRGSpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mRISpin->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( PaletteWindowGui::OnSpinCtrl ), NULL, this );
	mLockCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	mHexCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	mPalType->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	mCGAType->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	mCGAIntensity->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( PaletteWindowGui::OnCommandEvent ), NULL, this );
	
}

PaletteHolderGui::PaletteHolderGui( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	mPalHolderSizer = new wxFlexGridSizer( 2, 1, 0, 0 );
	mPalHolderSizer->AddGrowableCol( 0 );
	mPalHolderSizer->AddGrowableRow( 1 );
	mPalHolderSizer->SetFlexibleDirection( wxBOTH );
	mPalHolderSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	mPalHideBtn = new wxButton( this, wxID_ANY, wxT("Hide/Show palette"), wxDefaultPosition, wxSize( -1,16 ), 0 );
	mPalHolderSizer->Add( mPalHideBtn, 1, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	
	this->SetSizer( mPalHolderSizer );
	this->Layout();
	
	// Connect Events
	mPalHideBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PaletteHolderGui::OnPalHideBtnClick ), NULL, this );
}

PaletteHolderGui::~PaletteHolderGui()
{
	// Disconnect Events
	mPalHideBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PaletteHolderGui::OnPalHideBtnClick ), NULL, this );
	
}

ProjectWindowGui::ProjectWindowGui( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxGridSizer* gSizer5;
	gSizer5 = new wxGridSizer( 1, 1, 0, 0 );
	
	mProjectFilesList = new wxTreeListCtrl();
	mProjectFilesList->Create(this, wxID_ANY);
	gSizer5->Add( mProjectFilesList, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( gSizer5 );
	this->Layout();
}

ProjectWindowGui::~ProjectWindowGui()
{
}
