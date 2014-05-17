/***************************************************************
 * Name:      mainframeimpl.h
 * Purpose:   UttMainFrame implementation
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-01-17
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef MAINFRAMEIMPL_H_INCLUDED
#define MAINFRAMEIMPL_H_INCLUDED


#include "uttgui.h"



class MainFrameImpl:
	public UttMainFrame
{
public:
	MainFrameImpl();
	~MainFrameImpl(void);

	void Init();
	void Deinit();

private:

	void LoadConfig();
	void SaveConfig();

	virtual void OnClose( wxCloseEvent& event );
	virtual void OnMenuSelect( wxCommandEvent& event );
	void OnModuleMenuSelect( wxCommandEvent& event );

	void OnIdle( wxIdleEvent& event );
	void OnShow( wxShowEvent& event );

	void OnCommonEvent( CommonEvent& event );
	void OnAUIWindowEvent( AUIWindowEvent& event );
	void OnAUIManagerEvent( wxAuiManagerEvent& event );
	virtual void OnPaneClose( wxAuiManagerEvent& event );

	void OnEditorRebuildDataEvent( EditorRebuildDataEvent& event );

	void AddPane( wxWindow* wnd, const wxString& name, bool show );

	void UpdateMenuStates();
	bool DoCloseProject(bool force = false);
	bool CheckProject();
	void CreateNewProject();

	void LoadProject(const wxString& filename);
	void DoOpenProject();
	void DoSaveProject( bool saveAs = false );
	void DoSelectModule();
	void DoSelectVersion();
	void DoModuleChanged();
	void DoModuleCommand( int n );
	void DoShowHide( int id );
	void UpdateViewMenu( wxWindowID id, bool visible );
	void UpdateModuleMenu( const wxArrayString& strings );
	void ClearModuleMenu();
	void SetActivePane( wxWindow* wnd );

	wxHelpController*	mHelpController;
	ProjectPtr			mCurrentProject;
	wxAuiPaneInfo*		mCurrentPane;
	wxFileConfig		mConfig;
};

#endif
