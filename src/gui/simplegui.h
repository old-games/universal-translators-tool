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
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/treelist.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_SCROLLLEFT_BTN 2000
#define wxID_SCROLLRIGHT_BTN 2001
#define wxID_LR_SPIN 2002
#define wxID_LG_SPIN 2003
#define wxID_LB_SPIN 2004
#define wxID_LI_SPIN 2005
#define wxID_RB_SPIN 2006
#define wxID_RR_SPIN 2007
#define wxID_RG_SPIN 2008
#define wxID_RI_SPIN 2009
#define wxID_PALLOCK_CHECK 2010
#define wxID_HEX_CHECK 2011
#define wxID_PAL_CHOICE 2012
#define wxID_CGA_CHOICE 2013
#define wxID_INTENSITY_CHECK 2014

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
		virtual void OnMouseUp( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		BitmapRibbonGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,100 ), long style = wxTAB_TRAVERSAL ); 
		~BitmapRibbonGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PaletteWindowGui
///////////////////////////////////////////////////////////////////////////////
class PaletteWindowGui : public wxPanel 
{
	private:
	
	protected:
		wxStaticBoxSizer* mPalHolder;
		wxStaticText* m_staticText15;
		wxSpinCtrl* mLRSpin;
		wxStaticText* m_staticText16;
		wxSpinCtrl* mLGSpin;
		wxStaticText* m_staticText17;
		wxSpinCtrl* mLBSpin;
		wxStaticText* m_staticText22;
		wxSpinCtrl* mLISpin;
		wxStaticText* m_staticText18;
		wxSpinCtrl* mRBSpin;
		wxStaticText* m_staticText19;
		wxSpinCtrl* mRRSpin;
		wxStaticText* m_staticText20;
		wxSpinCtrl* mRGSpin;
		wxStaticText* m_staticText221;
		wxSpinCtrl* mRISpin;
		wxCheckBox* mLockCheck;
		wxCheckBox* mHexCheck;
		wxStaticText* m_staticText13;
		wxComboBox* mPalType;
		wxStaticText* m_staticText14;
		wxComboBox* mCGAType;
		wxCheckBox* mCGAIntensity;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSpinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnCommandEvent( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		PaletteWindowGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,300 ), long style = wxTAB_TRAVERSAL ); 
		~PaletteWindowGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class PaletteHolderGui
///////////////////////////////////////////////////////////////////////////////
class PaletteHolderGui : public wxPanel 
{
	private:
	
	protected:
		wxFlexGridSizer* mPalHolderSizer;
		wxButton* mPalHideBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPalHideBtnClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		PaletteHolderGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,25 ), long style = wxTAB_TRAVERSAL ); 
		~PaletteHolderGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ProjectWindowGui
///////////////////////////////////////////////////////////////////////////////
class ProjectWindowGui : public wxPanel 
{
	private:
	
	protected:
		wxTreeListCtrl* mProjectFilesList;
	
	public:
		
		ProjectWindowGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~ProjectWindowGui();
	
};

#endif //__SIMPLEGUI_H__
