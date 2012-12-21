/***************************************************************
 * Name:      projectwindow.h
 * Purpose:   Project window class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-21	 Doomsday!!! =)
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef PROJECTWINDOW_H_INCLUDED
#define PROJECTWINDOW_H_INCLUDED

#include "types/ieditor.h"

// forward declarations
class Project;

WX_DECLARE_HASH_MAP( wxUint32, wxTreeListItem, wxIntegerHash, wxIntegerEqual, TreeItemStorage );

class ProjectWindow: public ProjectWindowGui
{

public:
	ProjectWindow( wxWindow* parent );
	~ProjectWindow(void);

	void SetProject( Project* project );
	void UpdateProjectTree();
	void UpdateState( IEditor* editor );

private:

	void			Clear();
	void			InitTree();
	wxTreeListItem	GetTypeRoot( EditorType edType );
	void			SetItemState( wxTreeListItem item, IEditor* editor );

	Project*		mProject;
	wxTreeListItem	mTypeRoots[etNum];
	TreeItemStorage mEditorsItems;
};


#endif	// PROJECTWINDOW_H_INCLUDED
