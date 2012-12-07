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



LibTree::LibTree():
	mRoot( new LibItem(NULL, LIBITEM_ROOTID) ),
	mAllItems(),
	mAssignedTree(NULL)
{
	mRoot->SetText("Root");
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



LibItemId LibTree::AddItem( LibItemId parentId /* LIBITEM_ROOTID */)
{
	LibItem* parent = FindItem( parentId );

	LibItemId result = LIBITEM_BADID;

	if (parent)
	{
		LibItem* newItem = parent->AddChild();

		if (newItem)
		{
			result = newItem->GetId();
			mAllItems[result] = newItem;
		}
	}

	return result;
}



LibItem* LibTree::FindItem( LibItemId itemId )
{
	if (itemId == LIBITEM_ROOTID)
	{
		return mRoot;
	}

	ItemsMapIterator it = mAllItems.find( itemId );
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