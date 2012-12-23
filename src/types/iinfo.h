/***************************************************************
 * Name:      iinfo.h
 * Purpose:   declaration of IInfo interface
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-23
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef IINFO_H_INCLUDED
#define IINFO_H_INCLUDED

#include "origin.h"

// forward declarations


class IInfo: public IStateStore
{
public:

	IInfo( const wxString& infoName, int infoVersion, EditorType edType );
	IInfo( const IInfo& other );
	virtual ~IInfo();
	
	void SetOrigin( const Origin* origin );
	const Origin* GetOrigin() const;

	EditorType GetEditorType() const { return mEdType; }
protected:

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );

	Origin		mOrigin;
	EditorType	mEdType;
};



#endif // IINFO_H_INCLUDED
