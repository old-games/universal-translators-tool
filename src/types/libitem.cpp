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


LibItem::LibItem():
	mID(-1),
	mIsOk(false),
	mParent(NULL),
	mChildren()
{
}



LibItem::LibItem(LibItem* parent, unsigned int id):
	mID(id),
	mIsOk(parent),
	mParent(parent),
	mChildren()
{
}



LibItem::LibItem( const LibItem& item ):
	mID(item.mID),
	mIsOk(item.mIsOk),
	mParent(item.mParent),
	mChildren(item.mChildren)
{
}



LibItem::~LibItem()
{
}



