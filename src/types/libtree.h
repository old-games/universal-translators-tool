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



// forward declarations
class LibItem;



class LibTree
{
public:
	LibTree();
	virtual ~LibTree();

private:

	unsigned int	mID;
	LibItem*		mRoot;
};

#endif // LIBTREE_H_INCLUDED
