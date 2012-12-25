/***************************************************************
 * Name:      libitem.h
 * Purpose:   implementation of LibItem class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-06
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "libitem.h"

const LibItemId LIBITEM_BADID = 0xFFFFFFFF;
const LibItemId LIBITEM_ROOTID = 0;



LibItemData::LibItemData( const LibItemData& other ):
	mDataOwner( other.mDataOwner )
{
}



LibItem	LibItem::BAD_ITEM;



LibItem::LibItem():
	mID(LIBITEM_BADID),
	mText(wxEmptyString),
	mIsOk(false),
	mData(NULL),
	mParent(NULL),
	mChildren()
{
}



LibItem::LibItem(LibItem* parent, LibItemId id):
	mID(id),
	mText(wxEmptyString),
	mIsOk(parent != NULL),
	mData(NULL),
	mParent(parent),
	mChildren()
{
}



LibItem::LibItem( const LibItem& item ):
	mID(item.mID),
	mText(item.mText),
	mIsOk(item.mIsOk),
	mData(NULL),
	mParent(item.mParent),
	mChildren()
{
	if (item.mData)
	{
		mData = item.mData->Clone();
	}

	CopyChildren( item.mChildren );
}



/*virtual */ LibItem::~LibItem()
{
	ClearData();

	for (LibItemArray::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		delete *it;
	}

	mChildren.clear();
}



inline void LibItem::ParseId( LibItemId id, int &level, int& n )
{
	level = id >> 20;
	n = id & 0x000FFFFF;
}



inline LibItemId LibItem::PackId( int level, int n )
{
	wxASSERT( level <= 0xFFF && n <= 0xFFFFF );

	LibItemId result = level;
	result <<= 20;
	result |= n;
	return result;
}



inline LibItemId LibItem::CreateNewId()	// for children
{
	int level, n;
	ParseId( mID, level, n );
	return PackId( level + 1, mChildren.size() );
}



LibItem* LibItem::AddChild()
{
	LibItem* newItem = new LibItem( this, CreateNewId() );
	mChildren.Add( newItem );
	return newItem;
}



void LibItem::ClearData()
{
	if (mData)
	{
		delete mData;
		mData = NULL;
	}
}



void LibItem::SetData( LibItemData* data )
{
	ClearData();
	mData = data;
}



void LibItem::ChangeParentItem( LibItem* parent )
{
	mParent = parent;
	for (ItemsArrayIterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		(*it)->ChangeParentItem( this );
	}
}



void LibItem::CopyChildren( const LibItemArray& src )
{
	for (ConstItemsArrayIterator it = src.begin(); it != src.end(); ++it)
	{
		LibItem* newItem = (*it)->Clone();
		mChildren.Add( newItem );
		newItem->ChangeParentItem( this );
	}
}



void LibItem::CollectAllItems( LibItemsMap& dest )
{
	dest[ mID ] = this;

	for (ItemsArrayIterator it = mChildren.begin(); it != mChildren.end(); ++it)
	{
		(*it)->CollectAllItems( dest );
	}
}


