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
typedef LibItemArray::iterator ItemsArrayIterator;
typedef LibItemArray::const_iterator ConstItemsArrayItr;

typedef unsigned int LibItemId;
extern const LibItemId LIBITEM_BADID;
extern const LibItemId LIBITEM_ROOTID;



WX_DECLARE_HASH_MAP( LibItemId, LibItem*, wxIntegerHash, wxIntegerEqual, LibItemsMap );
typedef LibItemsMap::iterator ItemsMapIterator;
typedef LibItemsMap::const_iterator ConstItemsMapItr;


// this class to hold item id in wxTreeCtrl
class wxLibTreeData: public wxTreeItemData
{
public:
	wxLibTreeData(): mLibId( LIBITEM_BADID ) {}
	wxLibTreeData( LibItemId id ):	mLibId( id ) {}
	
	LibItemId mLibId;
};



struct LibItemData
{
	LibItemData();
	LibItemData( const LibItemData& other );
	
	virtual ~LibItemData() {}

	virtual LibItemData* Clone() { return new LibItemData(*this); }

	LibItemId		mDataOwner;
	wxFileOffset	mLibFileOffset;
	wxFileOffset	mLibDataSize;
};



class LibItem
{

public:
	LibItem();
	LibItem(LibItem* parent, LibItemId id);
	LibItem( const LibItem& item );

	virtual ~LibItem();

	LibItem* Clone() { return new LibItem(*this); }

	bool			IsOk() const { return mIsOk; }
	LibItemId		GetId() const { return mID; }
	wxString		GetText() const { return mText; }
	LibItemData*	GetData() const { return mData; }
	inline ItemsArrayIterator	GetChildrenBegin() { return mChildren.begin(); }
	inline ItemsArrayIterator	GetChildrenEnd() { return mChildren.end(); }
	
	void SetText(const wxString& txt) { mText = txt; }
	void SetText(const char* txt ) { mText = wxString(txt); }
	
	void SetData( LibItemData* data );
	void CollectAllItems( LibItemsMap& dest );

	LibItem* AddChild();

	static LibItem	BAD_ITEM;

private:
	void		ParseId( LibItemId id, int& level, int& n );
	LibItemId	PackId( int level, int n );
	LibItemId	CreateNewId();
	void		ClearData();
	void		ChangeParentItem( LibItem* parent );
	void		CopyChildren( const LibItemArray& src );

	LibItemId		mID;
	wxString		mText;
	bool			mIsOk;
	LibItemData*	mData;
	LibItem*		mParent;
	LibItemArray	mChildren;

};


#endif // LIBITEM_H_INCLUDED
