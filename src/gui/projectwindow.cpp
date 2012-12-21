/***************************************************************
 * Name:      projectwindow.cpp
 * Purpose:   Project window
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-21
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "projectwindow.h"
#include "types/project.h"
#include "types/origin.h"

namespace ProjectColumns
{
	enum
	{
		pcTree,
		pcState,
		pcOrirgin,
		pcNum
	};

	const wxString Names[pcNum] =
	{
		"Items",
		"State",
		"Origin"
	};
}



namespace ProjectMenu
{
	enum
	{
		pmAdd,
		pmRemove,
		pmNum
	};

	const wxString Commands[pmNum] =
	{
		"Add item",
		"Remove item"
	};
}


ProjectWindow::ProjectWindow(  wxWindow* parent ):
	ProjectWindowGui( parent ),
	mProject( NULL )
{
	InitTree();
}



ProjectWindow::~ProjectWindow(void)
{
	Clear();
}



void ProjectWindow::InitTree()
{
	for (size_t i = 0; i < ProjectColumns::pcNum; ++i)
	{
		mProjectFilesList->AppendColumn( ProjectColumns::Names[i] );
	}
}



wxTreeListItem ProjectWindow::GetTypeRoot( EditorType edType )
{
	if ( !mTypeRoots[edType].IsOk() )
	{
		mTypeRoots[edType] = mProjectFilesList->AppendItem( mProjectFilesList->GetRootItem(), sEditorNames[edType] );
	}

	return mTypeRoots[edType];
}



void ProjectWindow::Clear()
{
	mProjectFilesList->DeleteAllItems();
	mEditorsItems.clear();
	
	for (int i = 0; i < etNum; ++i)
	{
		mTypeRoots[i] = wxTreeListItem();
	}

	mProject = NULL;
}



void ProjectWindow::SetProject( Project* project )
{
	Clear();
	mProject = project;
	UpdateProjectTree();

	for (int i = 0; i < etNum; ++i)
	{
		if (mTypeRoots[i].IsOk())
		{
			mProjectFilesList->Expand( mTypeRoots[i] );
		}
	}

	for (int i = 0; i < ProjectColumns::pcNum; ++i)
	{
		mProjectFilesList->SetColumnWidth( i, wxCOL_WIDTH_AUTOSIZE );
	}
}



void ProjectWindow::UpdateProjectTree()
{
	if (!mProject)
	{
		return;
	}

	for ( size_t i = 0; i < mProject->GetEditorsNum(); ++i )
	{
		IEditor* editor = mProject->GetEditor( i );

		if (mEditorsItems.find(editor->GetEditorId()) != mEditorsItems.end())
		{
			continue;
		}

		wxTreeListItem root = GetTypeRoot( editor->GetType() );

		if (!root.IsOk())
		{
			wxLogError( "ProjectWindow::UpdateProjectTree: can't create root item for editor %s", editor->CreateName() );
			continue;
		}

		const Origin* origin = editor->GetOrigin();

		if (origin)
		{
			wxTreeListItem item = mProjectFilesList->AppendItem( root, origin->GetFileName() );

			if (item.IsOk())
			{
				mProjectFilesList->SetItemText(item, ProjectColumns::pcOrirgin, origin->GetPath() );
				SetItemState( item, editor );	
			}

			mEditorsItems[editor->GetEditorId()] = item;
		}
	}

}



void ProjectWindow::UpdateState( IEditor* editor )
{
	if (!editor)
	{
		return;
	}

	TreeItemStorage::iterator it = mEditorsItems.find( editor->GetEditorId() );
	
	if ( it != mEditorsItems.end() && it->second.IsOk() )
	{
		SetItemState( it->second, editor );
	}
}



inline void ProjectWindow::SetItemState( wxTreeListItem item, IEditor* editor )
{
	wxString state = editor->IsChanged() ? "*" : "";
	mProjectFilesList->SetItemText(item, ProjectColumns::pcState, state );
}