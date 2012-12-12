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

class FontEditor;
class LogWindowImpl;
class ImageEditor;
class PaletteWindowImpl;
class LibraryPanel;
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
	virtual void OnPageChanged( wxAuiNotebookEvent& event );
	void OnModuleMenuSelect( wxCommandEvent& event );

	void OnIdle( wxIdleEvent& );
	void OnShow( wxShowEvent& event );
	void OnColourPickEvent( ColourPickEvent& event );
	void OnModuleChanged( ModuleChangedEvent& event );

	void AddPane( wxWindow* wnd, const wxString& name );

	void UpdateMenuStates();
	void CloseProject(bool force = false);
	bool CheckProject();
	void CreateNewProject();

	void DoFileOpen();
	void DoSelectModule();
	void DoSelectVersion();
	void DoModuleChanged();
	void DoModuleCommand( int n );
	void UpdateModuleMenu( const wxArrayString& strings );
	void ClearModuleMenu();

	wxHelpController*		mHelpController;
	Project*				mCurrentProject;
	FontEditor*				mFontEditor;
	ImageEditor*			mEditWindow;
	PaletteWindowImpl*		mPalWindow;
	LibraryPanel*			mLibWindow;
};

#endif
