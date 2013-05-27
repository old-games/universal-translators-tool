/***************************************************************
 * Name:      libwindowimpl.h
 * Purpose:   Library window
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-06
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef LIBRARYPANEL_H_INCLUDED
#define LIBRARYPANEL_H_INCLUDED

#include "uttpanelsgui.h"
#include "types/ieditor.h"


//forward declarations
class LibTree;
class LibItem;
class wxLibTreeData;



class LibraryPanel : public LibraryGui, public IEditor
{

public:

	LibraryPanel( wxWindow* parent );
	virtual ~LibraryPanel(void);


	// from IEditor
	virtual bool SaveEditor();
	virtual bool LoadEditor();

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );

	virtual const Origin*	GetOrigin() const;
	virtual void SetInfo( IInfo* info );

protected:

	void OnTreeItemMenu( wxTreeListEvent& event );
	void OnItemExpanded( wxTreeListEvent& event );

private:

	void InitImageList();
	void InitTree();
	void SetColumnsWidth();
	wxLibTreeData* GetItemData( const wxTreeListItem& treeId );
	LibItem* GetLibItem( const wxTreeListItem& treeId );
	bool ExcludeChildrenFromArray( wxTreeListItems& items, const wxTreeListItem& treeId );
	void FillLibTree( const wxTreeListItem& treeId, LibItem* libItem );
	void DoContextMenu();
	wxMenu* GetItemActions( wxTreeListItems& selection );
	void AddActionToMenu( wxMenu*& menu, int action );
	
	void UpdateLibTree();
	void ClearLibrary();

	LibTree*		mLibInfo;
	wxImageList*	mImageList;
	wxTreeListItem	mRoot;
};




#endif
