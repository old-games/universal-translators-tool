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

typedef unsigned int LibItemId;
extern const LibItemId LIBITEM_BADID;
extern const LibItemId LIBITEM_ROOTID;



WX_DECLARE_HASH_MAP( LibItemId, LibItem*, wxIntegerHash, wxIntegerEqual, LibItemsMap );
typedef LibItemsMap::iterator ItemsMapIterator;

class LibItem
{

public:
	LibItem();
	LibItem(LibItem* parent, LibItemId id);
	LibItem( const LibItem& item );

	virtual ~LibItem();

	LibItem* Clone() { return new LibItem(*this); }

	bool IsOk() const { return mIsOk; }
	LibItemId GetId() const { return mID; }
	wxString GetText() const { return mText; }
	
	void SetText(const wxString& txt) { mText = txt; }

	LibItem* AddChild();

private:
	void ParseId( LibItemId id, int& level, int& n );
	LibItemId PackId( int level, int n );
	LibItemId CreateNewId();

	LibItemId		mID;
	wxString		mText;
	bool			mIsOk;
	LibItem*		mParent;
	LibItemArray	mChildren;

};


#endif // LIBITEM_H_INCLUDED
