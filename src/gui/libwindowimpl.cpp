/***************************************************************
 * Name:      libwindowimpl.cpp
 * Purpose:   Library window
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-06
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "libwindowimpl.h"
#include "types/libtree.h"
#include "luacontrol.h"
#include "luaexports/lualibtree.h"


#define INVALID_VALUE "Bad value"

namespace TreeGUIData
{
	enum Columns
	{
		cComponent,
		cSize,
		cOffset,
		cNum
	};
	
	const wxString ColumnText[cNum] = { "Component", "Size", "Offset" };
	const int ColumnWidth[cNum] = { 300, 100, 100 };
	
	enum 
	{
		File,
		Folder,
		Folder_Open,
		fNum
	};
	
	const char* const Icons[fNum] =
	{
		wxART_NORMAL_FILE,
		wxART_FOLDER,
		wxART_FOLDER_OPEN
	};
}


namespace ItemActions
{
	const int ID_START = 4000;
	
	enum
	{
		noAction = -1,
		// items with children
		extractToFolders,	// selection size > 0 extract as folders
		replaceWithFolder,	// selection size == 0 replace with folder
		// items without children
		extractAsFiles,		// selection size > 0 extract as files (user must select folder to extract)
		replaceWithFiles,	// selection size > 0 replace with files (user must select folder with files)
		itemRuntimeEdit,	// selection size == 1 edit item with something
		iaNum
	};

	const wxString Functions[iaNum] = {"libExtractFolders", "libReplaceFolder",
		"libExtractFiles", "libReplaceFiles", "libItemRuntimeEdit"};
	
	const wxString MenuText[iaNum] = {"Extract folders...", "Replace folder...",
		"Extract files...", "Replace files...", "Edit as"};
	
	//const wxWindowID ID[iaNum] = { ID_EXTRACT_FOLDERS, ID_REPLACE_FOLDER,
	//	ID_EXTRACT_FILE, ID_REPLACE_FILE, ID_RUNTIME_EDIT };
}



LibraryPanel::LibraryPanel( wxWindow* parent ):
	LibraryGui( parent ),
	IEditor( this, etLibrary, "Library editor" ),
	mLibInfo( NULL ),
	mImageList( NULL )
{
	mLibTree->Bind(wxEVT_TREELIST_ITEM_CONTEXT_MENU, &LibraryPanel::OnTreeItemMenu, this);
	mLibTree->Bind(wxEVT_TREELIST_ITEM_EXPANDED, &LibraryPanel::OnItemExpanded, this);
	InitImageList();
	InitTree();
}



LibraryPanel::~LibraryPanel(void)
{
	mLibTree->Unbind(wxEVT_TREELIST_ITEM_CONTEXT_MENU, &LibraryPanel::OnTreeItemMenu, this);
	mLibTree->Unbind(wxEVT_TREELIST_ITEM_EXPANDED, &LibraryPanel::OnItemExpanded, this);
	delete mImageList;
	ClearLibrary();
}



void LibraryPanel::InitImageList()
{
	wxSize iconSize = wxArtProvider::GetSizeHint(wxART_LIST);
	
	if ( iconSize == wxDefaultSize )
	{
		iconSize = wxSize(16, 16);
	}
	
	mImageList = new wxImageList(iconSize.x, iconSize.y);

	for ( unsigned n = 0; n < TreeGUIData::fNum; n++ )
	{
		mImageList->Add(wxArtProvider::GetIcon(TreeGUIData::Icons[n], wxART_LIST, iconSize));
	}
}



void LibraryPanel::InitTree()
{
	mLibTree->SetImageList(mImageList);

	for (int i = 0; i < TreeGUIData::cNum; ++i)
	{
		mLibTree->AppendColumn(TreeGUIData::ColumnText[i],
						TreeGUIData::ColumnWidth[i],
						i == 0 ? wxALIGN_LEFT : wxALIGN_RIGHT,
						wxCOL_RESIZABLE);// | (i == 0 ? wxCOL_SORTABLE : 0));
	}
}



void LibraryPanel::ClearLibrary()
{
	if (mLibInfo)
	{
		delete mLibInfo;
		mLibInfo = NULL;
	}
	
	UpdateLibTree();
}



void LibraryPanel::FillLibTree( const wxTreeListItem& treeId, LibItem* libItem )
{
	for (ItemsArrayIterator it = libItem->GetChildrenBegin(); 
		it != libItem->GetChildrenEnd(); ++it)
	{
		int imgOpen = (*it)->HasChildren() ? TreeGUIData::Folder : TreeGUIData::File;
		int imgClose = (*it)->HasChildren() ? TreeGUIData::Folder_Open : TreeGUIData::File;
		wxTreeListItem newTreeItem = mLibTree->AppendItem( treeId, (*it)->GetText(),
			imgOpen, imgClose);
		LibItemData* data = (*it)->GetData();
		
		if (data)
		{
			wxString value = data->mLibDataSize == wxInvalidOffset ? INVALID_VALUE :
				wxString::Format("%Ld", data->mLibDataSize);
			mLibTree->SetItemText(newTreeItem, TreeGUIData::cSize, value);
			
			value = data->mLibDataSize == wxInvalidOffset ? INVALID_VALUE :
				wxString::Format("%#.8Lx", data->mLibFileOffset);
			mLibTree->SetItemText(newTreeItem, TreeGUIData::cOffset, value);
		}
		
		mLibTree->SetItemData( newTreeItem, new wxLibTreeData((*it)->GetId()) );
		FillLibTree( newTreeItem, *it );
	}
	
	SetColumnsWidth();
}



void LibraryPanel::SetColumnsWidth()
{
	//mLibTree->SetColumnWidth(TreeGUIData::cComponent, wxCOL_WIDTH_AUTOSIZE);
	//mLibTree->SetColumnWidth(TreeGUIData::cSize, wxCOL_WIDTH_AUTOSIZE);
	//mLibTree->SetColumnWidth(TreeGUIData::cOffset, wxCOL_WIDTH_AUTOSIZE);
}



void LibraryPanel::UpdateLibTree()
{
	mLibTree->DeleteAllItems();
	
	if (!mLibInfo)
	{
		return;
	}
	
	//mLibInfo->AssignTreeCtrl(mLibTree);
	LibItem* rootItem = mLibInfo->GetRoot();
	mRoot = mLibTree->AppendItem(mLibTree->GetRootItem(), rootItem->GetText(),
		TreeGUIData::Folder, TreeGUIData::Folder_Open);
	FillLibTree( mRoot, rootItem );
}



void LibraryPanel::DoContextMenu()
{
	wxTreeListItems selection;
	wxMenu* menu = GetItemActions( selection );
	
	if (!menu)
	{
		return;
	}
	
	int action = mLibTree->GetPopupMenuSelectionFromUser(*menu);
	
	if (action != wxID_NONE)
	{
		OOLUA::Table items;
		OOLUA::new_table(Lua::Get(), items);
		
		for (size_t i = 0; i < selection.size(); ++i)
		{
			LibItem* item = GetLibItem(selection[i]);
			
			if (item)
			{
				items.set(i + 1, item);
			}
		}

		if (!Lua::Get().call("doModuleCommand", 
			ItemActions::Functions[action].ToStdString(), mLibInfo, items))
		{
			Lua::ShowLastError();
		}
	}
	
	delete menu;
}



wxMenu* LibraryPanel::GetItemActions( wxTreeListItems& selection )
{
	wxMenu* menu = NULL;
	
	mLibTree->GetSelections(selection);
	wxTreeListItems::iterator it = selection.begin();
	
	while(it != selection.end())
	{
		if (mLibTree->GetFirstChild(*it).IsOk())
		{
			if (ExcludeChildrenFromArray(selection, *it))
			{
				it = selection.begin();
				continue;
			}
		}
		
		++it;
	}
	
	it = selection.begin();
	bool hasWithChildren = false;
	bool hasWithoutChildren = false;
	bool isOne = selection.size() == 1;
	
	while(it != selection.end())
	{
		if (mLibTree->GetFirstChild(*it).IsOk())
		{
			hasWithChildren = true;
		}
		else
		{
			hasWithoutChildren = true;
		}
		++it;
	}
	
	if ( (!hasWithChildren && !hasWithoutChildren) ||
		 (hasWithChildren && hasWithoutChildren) )
	{
		wxLogMessage("Can't decide what to do with selected items!");
		return menu;
	}
	
	if (hasWithChildren)
	{
		AddActionToMenu(menu, ItemActions::extractToFolders);
		AddActionToMenu(menu, ItemActions::replaceWithFolder);
	}
	
	if (hasWithoutChildren)
	{
		AddActionToMenu(menu, ItemActions::extractAsFiles);
		AddActionToMenu(menu, ItemActions::replaceWithFiles);
		
		if (isOne)
		{
			AddActionToMenu(menu, ItemActions::itemRuntimeEdit);
		}
	}
	
	return menu;
}



void LibraryPanel::AddActionToMenu( wxMenu*& menu, int action )
{
	if (!Helpers::HasModuleFunction(ItemActions::Functions[action]))
	{
		return;
	}
	
	if (!menu)
	{
		menu = new wxMenu();
	}
	
	menu->Append(action, ItemActions::MenuText[action]);
}



template<typename T>
size_t wxFindIndex(const wxVector<T>& vect, const T& element)
{
	for (size_t i = 0; i < vect.size(); ++i)
	{
		if (vect[i] == element)
		{
			return i;
		}
	}
	
	return wxID_NONE;
}



template<typename T>
T* wxFind(wxVector<T>& vect, const T& element)
{
	wxVector<T>::iterator it = vect.begin();
	wxVector<T>::iterator end = vect.end();
	
	while (it != end)
	{
		if (*it == element)
		{
			return it;
		}
		
		++it;
	}
	
	return end;
}




bool LibraryPanel::ExcludeChildrenFromArray( wxTreeListItems& items, const wxTreeListItem& treeId )
{
	wxTreeListItem child = mLibTree->GetFirstChild(treeId);
	bool hasChanged = false;
	
	while (child.IsOk())
	{
		if (mLibTree->GetFirstChild(child).IsOk())
		{
			hasChanged = ExcludeChildrenFromArray(items, child);
		}
		
		wxTreeListItems::iterator it = wxFind(items, child);
		
		if (it != items.end())
		{
			items.erase(it);
			hasChanged = true;
		}
		child = mLibTree->GetNextSibling(child);
	}
	
	return hasChanged;
}



wxLibTreeData* LibraryPanel::GetItemData( const wxTreeListItem& treeId )
{
	return static_cast<wxLibTreeData*>(mLibTree->GetItemData(treeId));
}



LibItem* LibraryPanel::GetLibItem( const wxTreeListItem& treeId )
{
	wxLibTreeData* data = GetItemData(treeId);
	LibItem* res = NULL;
	
	if (data)
	{
		res = mLibInfo->FindItem(data->mLibId);
	}
	else if (treeId == mRoot)
	{
		res = mLibInfo->GetRoot();
	}
	
	return res;
}



void LibraryPanel::OnTreeItemMenu( wxTreeListEvent& event )
{
	DoContextMenu();
	event.Skip();
}



void LibraryPanel::OnItemExpanded( wxTreeListEvent& event )
{
	SetColumnsWidth();
	event.Skip();
}




/* virtual */ bool LibraryPanel::SaveEditor()
{
	return true;
}



/* virtual */ bool LibraryPanel::LoadEditor()
{
	return true;
}



/* virtual */ bool LibraryPanel::SaveState( wxOutputStream& /*output*/ )
{
	return true;
}



/* virtual */ bool LibraryPanel::LoadState( wxInputStream& /*input*/, int /*version*/ )
{
	return true;
}



/* virtual */ const Origin*	LibraryPanel::GetOrigin() const
{
	return mLibInfo ? mLibInfo->GetOrigin() : NULL;
}



/* virtual */ void LibraryPanel::SetInfo( IInfo* info )
{
	ClearLibrary();
	mLibInfo = static_cast<LibTree*>( info )->Clone();
	UpdateLibTree();
}


