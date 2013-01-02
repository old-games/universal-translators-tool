/***************************************************************
 * Name:      libtree.cpp
 * Purpose:   implementation of LibTree class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-06
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "libtree.h"


const wxString	LIBNAME = "LibTree";
const int		LIBVERSION = 0x100;



LibTree::LibTree():
	IInfo( LIBNAME, LIBVERSION, etLibrary ),
	mRoot( new LibItem(NULL, LIBITEM_ROOTID) ),
	mAllItems(),
	mAssignedTree(NULL)
{
	mRoot->SetText("Root");
}



LibTree::LibTree( const LibTree& other ):
	IInfo( other ),
	mRoot( other.mRoot->Clone() ),
	mAllItems(),
	mAssignedTree( other.mAssignedTree )
{
	mRoot->CollectAllItems( mAllItems );
}



/* virtual */ LibTree::~LibTree()
{
	delete mRoot;
}



void LibTree::DeleteItems()
{
	for (ItemsMapIterator it = GetItemsBegin(); it != GetItemsEnd(); ++it )
	{
		delete it->second;
	}
	mAllItems.clear();
}



LibItem* LibTree::AddItem( LibItem* parent /* NULL */ )
{
	if (!parent)
	{
		parent = mRoot;
	}
	
	LibItem* result = parent->AddChild();

	if (result)
	{
		mAllItems[result->GetId()] = result;
	}
	
	return result;
}



LibItemId LibTree::AddItem( LibItemId parentId /* LIBITEM_ROOTID */)
{
	LibItem* parent = FindItem( parentId );
	LibItemId result = LIBITEM_BADID;

	if (parent)
	{
		LibItem* newItem = this->AddItem( parent );

		if (newItem)
		{
			result = newItem->GetId();
		}
	}

	return result;
}



LibItem* LibTree::FindItem( LibItemId itemId ) const
{
	if (itemId == LIBITEM_ROOTID)
	{
		return mRoot;
	}

	ConstItemsMapItr it = mAllItems.find( itemId );
	
	if (it != mAllItems.end())
	{
		return it->second;
	}
	
	return NULL;
}



void LibTree::AssignTreeCtrl( wxTreeCtrl* tree )
{
	mAssignedTree = tree;
}