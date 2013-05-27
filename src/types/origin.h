/***************************************************************
 * Name:      origin.h
 * Purpose:   declaration of Origin class (stores information of object origin)
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef ORIGIN_H_INCLUDED
#define ORIGIN_H_INCLUDED



#include "istatestore.h"



class Origin: public IStateStore
{
public:

	enum OriginEnum
	{
		Unknown,
		FromFile,
		FromLibrary,
		MaxOrigins
	};

	Origin();
	Origin( const char* fileName );
	Origin( Origin* parent, wxFileOffset offset, wxFileOffset size );
	Origin( const Origin& other );
	virtual ~Origin();
	Origin* Clone() const { return new Origin(*this); }

	void SetOriginFileName( const wxString& fileName );
	void SetOriginAdditional( const wxString& additional );

	const wxString& GetFullPath() const;
	std::string LuaGetFullPath() const { return GetFullPath().ToStdString(); }

	wxString GetPath() const;
	wxString GetFileName() const;
	const Origin* GetParent() const;
	OriginEnum GetOrigin() const { return mOriginFrom; }

protected:
	
	void SetParent(const Origin* parent);
	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );
	
	OriginEnum		mOriginFrom;
	wxString		mOriginFileName;
	wxString		mOriginAdditional;
	wxFileOffset	mOffset;
	wxULongLong		mSize;
	Origin*			mParent;
};

#endif // ORIGIN_H_INCLUDED
