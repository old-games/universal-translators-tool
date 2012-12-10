/***************************************************************
 * Name:      libtree.h
 * Purpose:   declaration of LibTree class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-06
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef LIBTREE_H_INCLUDED
#define LIBTREE_H_INCLUDED


#include "libitem.h"



class LibTree
{
public:
	LibTree();
	virtual ~LibTree();

	void DeleteItems();

	LibItemId		AddItem( LibItemId parentId = LIBITEM_ROOTID );
	LibItem*		FindItem( LibItemId itemId );

	void			AssignTreeCtrl( wxTreeCtrl* tree );

protected:

	inline ItemsMapIterator GetItemsBegin() { return mAllItems.begin(); }
	inline ItemsMapIterator GetItemsEnd() { return mAllItems.end(); }

	LibItem* GetRoot() const { return mRoot; }

private:

	LibItem*			mRoot;
	LibItemsMap			mAllItems;
	wxTreeCtrl*			mAssignedTree;
};

#endif // LIBTREE_H_INCLUDED
