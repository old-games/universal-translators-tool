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
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include "projectwindow.h"
#include "logwindowimpl.h"
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_MAIN_FRAME 1000
#define wxID_NEW_PROJECT 1001
#define wxID_OPEN_PROJECT 1002
#define wxID_SAVE_PROJECT 1003
#define wxID_SAVE_PROJECT_AS 1004
#define wxID_CLOSE_PROJECT 1005
#define wxID_FILE_QUIT 1006
#define wxID_IMPORT_FONT 1007
#define wxID_IMPORT_IMAGE 1008
#define wxID_IMPORT_LIBRARY 1009
#define wxID_IMPORT_ANIMATION 1010
#define wxID_EXPORT_FONT 1011
#define wxID_EXPORT_IMAGE 1012
#define wxID_EXPORT_LIBRARY 1013
#define wxID_EXPORT_ANIMATION 1014
#define wxID_VIEW_TOOLBAR 1015
#define wxID_VIEW_PROJECT 1016
#define wxID_VIEW_LOG 1017
#define wxID_LUA_SELECT 1018
#define wxID_LUA_VERSION 1019
#define wxID_LUA_REBOOT 1020
#define wxID_HELP_HELP 1021
#define wxID_HELP_ABOUT 1022

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
		wxMenu* mViewMenu;
		wxMenu* mLuaMenu;
		wxMenu* mModuleMenu;
		wxMenu* mHelpMenu;
		wxAuiToolBar* mMainToolBar;
		ProjectWindow* mProjectWindow;
		LogWindowImpl* mLogWindow;
		wxStatusBar* mStatusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPaneClose( wxAuiManagerEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMenuSelect( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		UttMainFrame( wxWindow* parent, wxWindowID id = wxID_MAIN_FRAME, const wxString& title = wxT("UTT"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;
		
		~UttMainFrame();
	
};

#endif //__UTTGUI_H__
