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

class Project;



class MainFrameImpl:
	public UttMainFrame
{
public:
	MainFrameImpl();
	~MainFrameImpl(void);

	void Init();
	void Deinit();

private:

	virtual void OnClose( wxCloseEvent& event );
	virtual void OnMenuSelect( wxCommandEvent& event );
	void OnModuleMenuSelect( wxCommandEvent& event );

	void OnIdle( wxIdleEvent& );
	void OnShow( wxShowEvent& event );
	void OnColourPickEvent( ColourPickEvent& event );
	void OnModuleChanged( ModuleChangedEvent& event );
	void OnAUIWindowEvent( AUIWindowEvent& event );

	void AddPane( wxWindow* wnd, const wxString& name );

	void UpdateMenuStates();
	bool CloseProject(bool force = false);
	bool CheckProject();
	void CreateNewProject();

	void DoOpenProject();
	void DoSaveProject( bool saveAs = false );
	void DoSelectModule();
	void DoSelectVersion();
	void DoModuleChanged();
	void DoModuleCommand( int n );
	void UpdateModuleMenu( const wxArrayString& strings );
	void ClearModuleMenu();

	wxHelpController*		mHelpController;
	Project*				mCurrentProject;
};

#endif
