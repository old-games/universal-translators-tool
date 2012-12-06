/***************************************************************
 * Name:      libitem.h
 * Purpose:   declaration of LibItem class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-06
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef LIBITEM_H_INCLUDED
#define LIBITEM_H_INCLUDED



class LibItem;
WX_DEFINE_ARRAY( LibItem* , LibItemArray );



class LibItem
{

public:
	LibItem();
	LibItem(LibItem* parent, unsigned int id);
	LibItem( const LibItem& item );

	virtual ~LibItem();
	LibItem* Clone() { return new LibItem(*this); }

	bool IsOk() const { return mIsOk; }
private:

	unsigned int	mID;
	bool			mIsOk;
	LibItem*		mParent;
	LibItemArray	mChildren;

};


#endif // LIBITEM_H_INCLUDED
