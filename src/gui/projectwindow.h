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



class ProjectItemData: public wxClientData
{
public:
	IEditor*	mEditor;
};

class ProjectWindow: public ProjectWindowGui
{

public:
	ProjectWindow( wxWindow* parent, wxWindowID id );
	~ProjectWindow(void);

	void SetProject( Project* project );
	bool SetEditor( wxWindow* wnd );	// highlight current editor
	void UpdateProjectTree();
	void UpdateState( IEditor* editor );

protected:

	virtual void OnLeftDblClick( wxMouseEvent& event );
	void OnTreeListContextMenu( wxTreeListEvent& event );
	void OnTreeListChanged( wxTreeListEvent& event );

private:

	void			Clear();
	void			InitTree();

	void DoItemContextMenu( wxTreeListItem item );
	void DoCategoryContextMenu( wxTreeListItem item );
	void HideShowChildren( wxTreeListItem item, bool hide );

	wxTreeListItem	GetTypeRoot( EditorType edType );
	void			SetItemState( wxTreeListItem item, IEditor* editor );

	wxTreeListItem	GetEditorItem( IEditor* editor );
	ProjectItemData*GetItemData( wxTreeListItem item ) const;

	Project*		mProject;

	wxMenu*			mItemMenu;
	wxMenu*			mCategoryMenu;

	wxTreeListItem	mTypeRoots[etNum];
	TreeItemStorage mEditorsItems;

	wxDECLARE_EVENT_TABLE();

};


#endif	// PROJECTWINDOW_H_INCLUDED
