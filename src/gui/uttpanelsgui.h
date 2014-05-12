///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 26 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __UTTPANELSGUI_H__
#define __UTTPANELSGUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include "bmpribbonctrl.h"
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/scrolwin.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/treelist.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/bmpbuttn.h>
#include <wx/slider.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_CREATE_FONT 1000
#define wxID_SAVE_BTN 1001
#define wxID_LOAD_BTN 1002
#define wxID_FONT_SETTINGS 1003
#define wxID_GRID_CHECK 1004
#define wxID_GRID_MODE 1005
#define wxID_GRIDCOL_BTN 1006
#define wxID_LIBRARYWINDOW 1007
#define wxID_LIBTREE 1008
#define wxID_PLAY_BTN 1009
#define wxID_BACKWARD_BTN 1010
#define wxID_STOP_BTN 1011
#define wxID_FORWARD_BTN 1012
#define wxID_VIDEO_SLIDER 1013

///////////////////////////////////////////////////////////////////////////////
/// Class FontEditGui
///////////////////////////////////////////////////////////////////////////////
class FontEditGui : public wxPanel 
{
	private:
	
	protected:
		wxScrolledWindow* mFontScrolledBack;
		wxButton* mCreateBtn;
		wxButton* mSaveBtn;
		wxButton* mLoadBtn;
		wxButton* mSettingsBtn;
		wxSplitterWindow* mFontSplitter;
		wxPanel* mRibbonOwner;
		BitmapRibbonCtrl* mSymbolsRibbon;
		wxPanel* mSymEditorOwner;
		wxGridSizer* mCentralSizer;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnBtnClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		FontEditGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,442 ), long style = wxTAB_TRAVERSAL ); 
		~FontEditGui();
		
		void mFontSplitterOnIdle( wxIdleEvent& )
		{
			mFontSplitter->SetSashPosition( 64 );
			mFontSplitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( FontEditGui::mFontSplitterOnIdle ), NULL, this );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class EditPanelGui
///////////////////////////////////////////////////////////////////////////////
class EditPanelGui : public wxPanel 
{
	private:
	
	protected:
		wxScrolledWindow* mEditScrolledBack;
		wxFlexGridSizer* mEditSizer;
		wxStaticBoxSizer* mDrawHolder;
		wxCheckBox* mGridCheck;
		wxStaticText* m_staticText12;
		wxChoice* mGridModeChoice;
		wxButton* mGetGridColour;
		wxButton* mSaveBtn;
		wxButton* mLoadBtn;
		wxGridSizer* mPalSizer;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCommandEvent( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		EditPanelGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,400 ), long style = wxTAB_TRAVERSAL|wxWANTS_CHARS ); 
		~EditPanelGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class LibraryGui
///////////////////////////////////////////////////////////////////////////////
class LibraryGui : public wxPanel 
{
	private:
	
	protected:
		wxScrolledWindow* mLibScrolledBack;
		wxTreeListCtrl* mLibTree;
	
	public:
		
		LibraryGui( wxWindow* parent, wxWindowID id = wxID_LIBRARYWINDOW, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 509,482 ), long style = wxTAB_TRAVERSAL ); 
		~LibraryGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class VideoPanelGui
///////////////////////////////////////////////////////////////////////////////
class VideoPanelGui : public wxPanel 
{
	private:
	
	protected:
		wxGridSizer* mVideoSizer;
		wxBitmapButton* mPlayBtn;
		wxBitmapButton* mBackBtn;
		wxBitmapButton* mStopBtn;
		wxBitmapButton* mForwardBtn;
		wxSlider* mPosSlider;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSlider( wxScrollEvent& event ) { event.Skip(); }
		
	
	public:
		
		VideoPanelGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL ); 
		~VideoPanelGui();
	
};

#endif //__UTTPANELSGUI_H__
