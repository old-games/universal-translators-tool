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
