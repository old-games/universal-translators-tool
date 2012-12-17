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
	mScrollLeftBtn->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_MIDDLE_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_MIDDLE_UP, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_MOTION, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_MIDDLE_DCLICK, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollRightBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BitmapRibbonGui::OnButtonClick ), NULL, this );
	mScrollRightBtn->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseDown ), NULL, this );
	mScrollRightBtn->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( BitmapRibbonGui::OnMouseUp ), NULL, this );
}

BitmapRibbonGui::~BitmapRibbonGui()
{
	// Disconnect Events
	mScrollLeftBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BitmapRibbonGui::OnButtonClick ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseDown ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_MIDDLE_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_MIDDLE_UP, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_MOTION, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_MIDDLE_DCLICK, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_RIGHT_DCLICK, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollLeftBtn->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( BitmapRibbonGui::OnMouseEvents ), NULL, this );
	mScrollRightBtn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BitmapRibbonGui::OnButtonClick ), NULL, this );
	mScrollRightBtn->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BitmapRibbonGui::OnMouseDown ), NULL, this );
	mScrollRightBtn->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( BitmapRibbonGui::OnMouseUp ), NULL, this );
	
}

CreateProjectGui::CreateProjectGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	
	this->Centre( wxBOTH );
}

CreateProjectGui::~CreateProjectGui()
{
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
