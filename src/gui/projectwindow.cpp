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



namespace ItemMenu
{
	enum
	{
		imOpen,
		imClose,
		imExport,
		imExclude,
		imNum
	};

	const wxString Commands[imNum] =
	{
		"Open pane",
		"Close pane",
		"Export...",
		"Exclude from project"
	};
}



namespace CategoryMenu
{
	enum
	{
		cmOpen,
		cmClose,
		cmImport,
		cmNum
	};

	const wxString Commands[cmNum] =
	{
		"Open all",
		"Close all",
		"Import..."
	};
}



BEGIN_EVENT_TABLE(ProjectWindow, ProjectWindowGui)	
	EVT_TREELIST_SELECTION_CHANGED(wxID_ANY, ProjectWindow::OnTreeListChanged)
	EVT_TREELIST_ITEM_CONTEXT_MENU(wxID_ANY, ProjectWindow::OnTreeListContextMenu)
END_EVENT_TABLE()



ProjectWindow::ProjectWindow(  wxWindow* parent, wxWindowID id ):
	ProjectWindowGui( parent, id ),
	mProject( NULL ),
	mItemMenu( new wxMenu() ),
	mCategoryMenu( new wxMenu() )
{
	this->Bind( wxEVT_LEFT_DCLICK, &ProjectWindow::OnLeftDblClick, this, mProjectFilesList->GetId() );
	InitTree();
}



ProjectWindow::~ProjectWindow(void)
{
	this->Unbind( wxEVT_LEFT_DCLICK, &ProjectWindow::OnLeftDblClick, this, mProjectFilesList->GetId() );
	Clear();

	delete mItemMenu;
	delete mCategoryMenu;
}



void ProjectWindow::InitTree()
{
	for (int i = 0; i < ItemMenu::imNum; ++i)
	{
		mItemMenu->Append(i, ItemMenu::Commands[i]);
	}

	for (int i = 0; i < CategoryMenu::cmNum; ++i)
	{
		mCategoryMenu->Append(i, CategoryMenu::Commands[i]);
	}

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



wxTreeListItem ProjectWindow::GetEditorItem( IEditor* editor )
{
	wxTreeListItem res;

	if (editor)
	{
		TreeItemStorage::iterator it = mEditorsItems.find(editor->GetEditorId());

		if (it != mEditorsItems.end())
		{
			res = it->second;
		}
	}

	return res;
}



bool ProjectWindow::SetEditor( wxWindow* wnd )
{
	if (mProject)
	{
		wxTreeListItem item = GetEditorItem( mProject->FindEditor( wnd ) );
		
		if (item.IsOk())
		{
			mProjectFilesList->Select( item );
			return true;
		}
	}
	return false;
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

				ProjectItemData* data = new ProjectItemData();
				data->mEditor = editor;

				mProjectFilesList->SetItemData( item, data );
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



void ProjectWindow::DoItemContextMenu( wxTreeListItem item )
{
	AUIWindowEvent* event = NULL;
	ProjectItemData* data = GetItemData( item );

    switch ( this->GetPopupMenuSelectionFromUser( *mItemMenu ) )
	{
		case ItemMenu::imOpen:
			event = new AUIWindowEvent( AUIWindowEvent::ShowWindow, data->mEditor->GetWindow() );
		break;

		case ItemMenu::imClose:
			event = new AUIWindowEvent( AUIWindowEvent::HideWindow, data->mEditor->GetWindow() );
		break;

		case ItemMenu::imExport:
		break;

		case ItemMenu::imExclude:
			if ( AREYOUSURE("Exclude this file from project?") == wxID_YES )
			{
				mProject->RemoveEditor( data->mEditor );
				mProjectFilesList->DeleteItem( item );
			}
		break;

		case wxID_NONE:
		break;

		default:
			wxLogError( "ProjectWindow::DoItemContextMenu: unexpected menu selection" );
	}

	if (event)
	{
		wxTheApp->QueueEvent( event );
	}
}



void ProjectWindow::DoCategoryContextMenu( wxTreeListItem item )
{
	switch ( this->GetPopupMenuSelectionFromUser( *mCategoryMenu ) )
	{
		case CategoryMenu::cmOpen:
			HideShowChildren( item, false );
		break;

		case CategoryMenu::cmClose:
			HideShowChildren( item, true );
		break;

		case CategoryMenu::cmImport:

		break;

		case wxID_NONE:
		break;

		default:
			wxLogError( "ProjectWindow::DoCategoryContextMenu: unexpected menu selection" );
	}
}



void ProjectWindow::HideShowChildren( wxTreeListItem item, bool hide )
{
	wxTreeListItem child = mProjectFilesList->GetFirstChild(item);

	while (child.IsOk())
	{
		ProjectItemData* data = GetItemData( child );

		if (data)
		{
			AUIWindowEvent* event = new AUIWindowEvent( hide ? AUIWindowEvent::HideWindow : AUIWindowEvent::ShowWindow, data->mEditor->GetWindow() );
			wxTheApp->QueueEvent( event );
		}

		child = mProjectFilesList->GetNextSibling( child );
	}
}



inline void ProjectWindow::SetItemState( wxTreeListItem item, IEditor* editor )
{
	wxString state = editor->IsChanged() ? "*" : "";
	mProjectFilesList->SetItemText(item, ProjectColumns::pcState, state );
}



inline ProjectItemData* ProjectWindow::GetItemData( wxTreeListItem item ) const
{
	return static_cast<ProjectItemData*> (mProjectFilesList->GetItemData( item ));
}



void ProjectWindow::OnTreeListContextMenu( wxTreeListEvent& event )
{
	if ( GetItemData( event.GetItem() ) )
	{
		DoItemContextMenu( event.GetItem() );
	}
	else
	{
		DoCategoryContextMenu( event.GetItem() );
	}
	event.Skip();
}



void ProjectWindow::OnTreeListChanged( wxTreeListEvent& event )
{
	ProjectItemData* data = GetItemData( event.GetItem() );

	if (data && data->mEditor)
	{
		AUIWindowEvent* event = new AUIWindowEvent( AUIWindowEvent::SetActive, data->mEditor->GetWindow() );
		wxTheApp->QueueEvent( event );
	}

	event.Skip();
}



/* virtual */ void ProjectWindow::OnLeftDblClick( wxMouseEvent& event ) 
{ 
	// TODO: wait =) wxTreeListCtrl don't generates dblclick events yet
	//wxHitTest tst  = mProjectFilesList->HitTest( event.GetPosition() );
	event.Skip(); 
}