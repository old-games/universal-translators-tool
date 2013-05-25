///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __UTTDIALOGSGUI_H__
#define __UTTDIALOGSGUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/grid.h>
#include <wx/panel.h>
#include <wx/combobox.h>
#include <wx/filepicker.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_FONT_SETTINGS_ID 1000
#define wxID_NUM_SPIN_CTRL 1001
#define wxID_SET_CODES_BTN 1002
#define wxID_MAX_WIDTH_SPIN 1003
#define wxID_MAX_HEIGHT_SPIN 1004
#define wxID_MIN_WIDTH_SPIN 1005
#define wxID_MIN_HEIGHT_SPIN 1006
#define wxID_BASE_LINE_SPIN 1007
#define wxID_CAP_LINE_SPIN 1008
#define wxID_LOW_LINE_SPIN 1009
#define wxID_LETTER_CODES_ID 1010
#define wxID_GENERATE_CODES_BTN 1011
#define wxID_GET_ENCODING_BTN 1012
#define wxID_CODES_GRID 1013
#define wxID_SELECT_MODULE_ID 1014
#define wxID_CREATE_PROJECT_DLG 1015

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

///////////////////////////////////////////////////////////////////////////////
/// Class CreateProjectGui
///////////////////////////////////////////////////////////////////////////////
class CreateProjectGui : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxFilePickerCtrl* mFileDlg;
		wxStaticText* m_staticText11;
		wxDirPickerCtrl* mDirDlg;
		wxStaticText* m_staticText2;
		wxComboBox* mModulesCombo;
		wxStaticText* m_staticText3;
		wxComboBox* mVersionsCombo;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnProjectFileNameChanged( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void OnModuleChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		CreateProjectGui( wxWindow* parent, wxWindowID id = wxID_CREATE_PROJECT_DLG, const wxString& title = wxT("Create new project"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 465,261 ), long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU ); 
		~CreateProjectGui();
	
};

#endif //__UTTDIALOGSGUI_H__
