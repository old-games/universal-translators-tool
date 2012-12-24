/***************************************************************
 * Name:      project.h
 * Purpose:   declaration of Project container class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED



#include "istatestore.h"
#include "types/ieditor.h"

enum IECommands
{
	iecImport,
	iecExport,
	iecNum
};

extern const wxString sCommandNames[iecNum];



class Project: public IStateStore
{
public:

	Project();
	Project::Project( const Project& other );
	~Project();

	bool IsChanged() const { return mChanged; }
	bool CheckChanged();

	bool CreateProject( const wxString& fullPath, const wxString& gamePath, const wxString& module, const wxString& version );
	bool SaveProject( const wxString& saveAs = wxEmptyString );
	bool LoadProject( const wxString& fullPath );

	void CloseProject();
	void RemoveEditor( IEditor* editor );

	const wxString& GetProjectFileName() const { return mProjectFileName; }
	const wxString& GetName() const { return mProjectName; }
	const wxString& GetPerspective( ) const { return mPerspective; }

	bool SetActiveModule();
	bool SetActiveModule( const wxString& module, const wxString& version );
	void SetPerspective( const wxString& perspective ) { mPerspective = perspective; }

	bool IsAllowed( IECommands what, EditorType who );
	bool Do( IECommands what, EditorType who );

	size_t GetEditorsNum() const { return mEditors.GetCount(); }
	IEditor* GetEditor( size_t n ) const { return mEditors[n]; }
	IEditor* FindEditor( wxWindow* wnd ) const;

protected:

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );

	virtual void OnChangeInfoEvent( ChangeInfoEvent& event );
	virtual void OnEditorRebuildDataEvent( EditorRebuildDataEvent& event );
	
private:

	void			BindEvents();

	void			CreateEditorAndSetIt( IInfo* info );
	void			CloseEditor( IEditor* editor, bool update );

	void			AddEditorWindow( IEditor* editor, const wxString& wndName, bool update );
	void			SendUpdateEvent();
	void			SendSetCaptionEvent( IEditor* editor );

	wxString		GetFunctionName( IECommands what, EditorType who );
	bool			SaveEditors( wxOutputStream& output );
	bool			LoadEditors( wxInputStream& input );

	bool			mChanged;
	wxString		mProjectName;
	wxString		mModuleName;
	wxString		mModuleVersion;
	wxString		mLastDir;
	wxString		mGamePath;
	wxString		mProjectFileName;
	wxString		mPerspective;

	EditorsArray	mEditors;
};

#endif // PROJECT_H_INCLUDED
