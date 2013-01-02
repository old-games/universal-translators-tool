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


#include "iinfo.h"
#include "libitem.h"



class LibTree: public IInfo
{
public:
	LibTree();
	LibTree( const LibTree& other );
	virtual ~LibTree();

	LibTree* Clone() { return new LibTree(*this); }
	void DeleteItems();

	LibItem*		AddItem( LibItem* parent = NULL );
	LibItemId		AddItem( LibItemId parentId = LIBITEM_ROOTID );
	
	LibItem*		FindItem( LibItemId itemId ) const;
	LibItem*		GetRoot() const { return mRoot; }

	void			AssignTreeCtrl( wxTreeCtrl* tree );

protected:

	inline ItemsMapIterator GetItemsBegin() { return mAllItems.begin(); }
	inline ItemsMapIterator GetItemsEnd() { return mAllItems.end(); }

private:

	LibItem*			mRoot;
	LibItemsMap			mAllItems;
	wxTreeCtrl*			mAssignedTree;
};

#endif // LIBTREE_H_INCLUDED
