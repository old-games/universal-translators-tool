///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __SIMPLEGUI_H__
#define __SIMPLEGUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/bmpbuttn.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/dialog.h>
#include <wx/combobox.h>
#include <wx/statbox.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_BITMAP_RIBBON 2000
#define wxID_SCROLLLEFT_BTN 2001
#define wxID_SCROLLRIGHT_BTN 2002
#define wxID_CREATE_PROJECT_DLG 2003
#define wxID_SELECT_MODULE_ID 2004

///////////////////////////////////////////////////////////////////////////////
/// Class BitmapRibbonGui
///////////////////////////////////////////////////////////////////////////////
class BitmapRibbonGui : public wxPanel 
{
	private:
	
	protected:
		wxBitmapButton* mScrollLeftBtn;
		wxBoxSizer* mBitmapsHolder;
		wxBitmapButton* mScrollRightBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMouseDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMouseEvents( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMouseUp( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		BitmapRibbonGui( wxWindow* parent, wxWindowID id = wxID_BITMAP_RIBBON, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,100 ), long style = wxTAB_TRAVERSAL ); 
		~BitmapRibbonGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CreateProjectGui
///////////////////////////////////////////////////////////////////////////////
class CreateProjectGui : public wxDialog 
{
	private:
	
	protected:
	
	public:
		
		CreateProjectGui( wxWindow* parent, wxWindowID id = wxID_CREATE_PROJECT_DLG, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 478,393 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~CreateProjectGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutBoxGui
///////////////////////////////////////////////////////////////////////////////
class AboutBoxGui : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_panel3;
		wxButton* mCloseButton;
	
	public:
		
		AboutBoxGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 505,371 ), long style = wxDIALOG_NO_PARENT ); 
		~AboutBoxGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SelectModuleGui
///////////////////////////////////////////////////////////////////////////////
class SelectModuleGui : public wxDialog 
{
	private:
	
	protected:
		wxComboBox* mModulesChoice;
		wxButton* mOkBtn;
		wxButton* mCancelBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnBtnClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		SelectModuleGui( wxWindow* parent, wxWindowID id = wxID_SELECT_MODULE_ID, const wxString& title = wxT("Select Lua module:"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 307,106 ), long style = wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU ); 
		~SelectModuleGui();
	
};

#endif //__SIMPLEGUI_H__
