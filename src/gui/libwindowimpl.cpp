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

LibraryPanel::LibraryPanel( wxWindow* parent ):
	LibraryGui( parent ),
	IEditor( this, etLibrary, "Library editor" ),
	mLibInfo( NULL )
{
}



LibraryPanel::~LibraryPanel(void)
{
	ClearLibrary();
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



void LibraryPanel::FillLibTree( wxTreeItemId treeId, LibItem* libItem )
{
	for (ItemsArrayIterator it = libItem->GetChildrenBegin(); 
		it != libItem->GetChildrenEnd(); ++it)
	{
		wxTreeItemId newTreeItem = mLibTree->AppendItem( treeId, (*it)->GetText() );
		mLibTree->SetItemData( newTreeItem, new wxLibTreeData((*it)->GetId()) );
		FillLibTree( newTreeItem, *it );
	}
}



void LibraryPanel::UpdateLibTree()
{
	mLibTree->DeleteAllItems();
	
	if (!mLibInfo)
	{
		return;
	}
	
	wxTreeItemId root = mLibTree->AddRoot("root");
	
	FillLibTree( root, mLibInfo->GetRoot() );
}



/* virtual */ bool LibraryPanel::SaveEditor()
{
	return true;
}



/* virtual */ bool LibraryPanel::LoadEditor()
{
	return true;
}



/* virtual */ bool LibraryPanel::SaveState( wxOutputStream& output )
{
	return true;
}



/* virtual */ bool LibraryPanel::LoadState( wxInputStream& input, int version )
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


