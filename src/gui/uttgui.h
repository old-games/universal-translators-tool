///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __UTTGUI_H__
#define __UTTGUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/aui/auibook.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include "logwindowimpl.h"
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/grid.h>
#include "bmpribbonctrl.h"
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include "palholderctrl.h"
#include <wx/treectrl.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_MAIN_FRAME 1000
#define wxID_NEW_PROJECT 1001
#define wxID_OPEN_PROJECT 1002
#define wxID_SAVE_PROJECT 1003
#define wxID_SAVE_PROJECT_AS 1004
#define wxID_FILE_QUIT 1005
#define wxID_IMPORT_FONT 1006
#define wxID_IMPORT_IMAGE 1007
#define wxID_IMPORT_LIBRARY 1008
#define wxID_IMPORT_ANIMATION 1009
#define wxID_EXPORT_FONT 1010
#define wxID_EXPORT_IMAGE 1011
#define wxID_EXPORT_LIBRARY 1012
#define wxID_EXPORT_ANIMATION 1013
#define wxID_LUA_SELECT 1014
#define wxID_LUA_VERSION 1015
#define wxID_LUA_REBOOT 1016
#define wxID_HELP_HELP 1017
#define wxID_HELP_ABOUT 1018
#define wxID_FONT_SETTINGS_ID 1019
#define wxID_NUM_SPIN_CTRL 1020
#define wxID_SET_CODES_BTN 1021
#define wxID_MAX_WIDTH_SPIN 1022
#define wxID_MAX_HEIGHT_SPIN 1023
#define wxID_MIN_WIDTH_SPIN 1024
#define wxID_MIN_HEIGHT_SPIN 1025
#define wxID_BASE_LINE_SPIN 1026
#define wxID_CAP_LINE_SPIN 1027
#define wxID_LOW_LINE_SPIN 1028
#define wxID_LETTER_CODES_ID 1029
#define wxID_GENERATE_CODES_BTN 1030
#define wxID_GET_ENCODING_BTN 1031
#define wxID_CODES_GRID 1032
#define wxID_CREATE_FONT 1033
#define wxID_SAVE_BTN 1034
#define wxID_LOAD_BTN 1035
#define wxID_FONT_SETTINGS 1036
#define wxID_IMAGEEDITOR 1037
#define wxID_GRID_CHECK 1038
#define wxID_GRID_MODE 1039
#define wxID_GRIDCOL_BTN 1040
#define wxID_LIBRARYWINDOW 1041
#define wxID_LIBTREE 1042

///////////////////////////////////////////////////////////////////////////////
/// Class UttMainFrame
///////////////////////////////////////////////////////////////////////////////
class UttMainFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mMainMenu;
		wxMenu* mFileMenu;
		wxMenu* mImportExportMenu;
		wxMenu* mEditMenu;
		wxMenu* mLuaMenu;
		wxMenu* mModuleMenu;
		wxMenu* mHelpMenu;
		wxAuiNotebook* mAUINotebook;
		wxAuiToolBar* mMainToolBar;
		LogWindowImpl* mLogWindow;
		wxStatusBar* mStatusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPageChanged( wxAuiNotebookEvent& event ) { event.Skip(); }
		
	
	public:
		
		UttMainFrame( wxWindow* parent, wxWindowID id = wxID_MAIN_FRAME, const wxString& title = wxT("UTT"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;
		
		~UttMainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class FontSettingsGui
///////////////////////////////////////////////////////////////////////////////
class FontSettingsGui : public wxDialog 
{
	private:
	
	protected:
		wxScrolledWindow* m_scrolledWindow1;
		wxStaticText* m_staticText1;
		wxSpinCtrl* mNumSpinCtrl;
		wxStaticText* m_staticText2;
		wxButton* mSetCodesBtn;
		wxStaticText* m_staticText5;
		wxSpinCtrl* mMaxWidthSpinCtrl;
		wxStaticText* m_staticText3;
		wxSpinCtrl* mMaxHeightSpinCtrl;
		wxStaticText* m_staticText6;
		wxSpinCtrl* mMinWidthSpinCtrl;
		wxStaticText* m_staticText4;
		wxSpinCtrl* mMinHeightSpinCtrl;
		wxStaticText* m_staticText8;
		wxSpinCtrl* mBaseLineSpinCtrl;
		wxStaticText* m_staticText9;
		wxSpinCtrl* mCapLineSpinCtrl;
		wxStaticText* m_staticText10;
		wxSpinCtrl* mLowLineSpinCtrl;
		wxButton* mOkBtn;
		wxButton* mCancelBtn;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSpinCtrl( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnBtnClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		FontSettingsGui( wxWindow* parent, wxWindowID id = wxID_FONT_SETTINGS_ID, const wxString& title = wxT("Font settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 290,363 ), long style = wxCAPTION|wxCLOSE_BOX|wxSTAY_ON_TOP|wxSYSTEM_MENU ); 
		~FontSettingsGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class LetterCodesGui
///////////////////////////////////////////////////////////////////////////////
class LetterCodesGui : public wxDialog 
{
	private:
	
	protected:
		wxScrolledWindow* m_scrolledWindow2;
		wxStaticBoxSizer* mAutoSizer;
		wxStaticText* m_staticText11;
		wxSpinCtrl* mInitialSpinCtrl;
		wxButton* mGenerateBtn;
		wxStaticText* m_staticText111;
		wxTextCtrl* mCodeTxt;
		wxButton* mGetEncodingBtn;
		wxStaticBoxSizer* mBtnsSizer;
		wxButton* mOkBtn;
		wxButton* mCancelBtn;
		wxStaticBoxSizer* mGridSizer;
		wxGrid* mCodesGrid;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnBtnClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		LetterCodesGui( wxWindow* parent, wxWindowID id = wxID_LETTER_CODES_ID, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,500 ), long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER|wxSTAY_ON_TOP|wxSYSTEM_MENU ); 
		~LetterCodesGui();
	
};

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
		wxStaticBoxSizer* mDrawHolder;
		wxCheckBox* mGridCheck;
		wxStaticText* m_staticText12;
		wxChoice* mGridModeChoice;
		wxButton* mGetGridColour;
		wxButton* mSaveBtn;
		wxButton* mLoadBtn;
		PaletteHolderCtrl* mPaletteHolder;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCommandEvent( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		EditPanelGui( wxWindow* parent, wxWindowID id = wxID_IMAGEEDITOR, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 640,400 ), long style = wxTAB_TRAVERSAL|wxWANTS_CHARS ); 
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
		wxTreeCtrl* mLibTree;
	
	public:
		
		LibraryGui( wxWindow* parent, wxWindowID id = wxID_LIBRARYWINDOW, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 509,482 ), long style = wxTAB_TRAVERSAL ); 
		~LibraryGui();
	
};

#endif //__UTTGUI_H__
