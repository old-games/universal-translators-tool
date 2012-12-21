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
	Origin( OriginEnum origin, const char* fileName );
	Origin( const Origin& other );

	void SetOriginFileName( const wxString& fileName );
	void SetOriginAdditional( const wxString& additional );

	const wxString& GetFullPath() const;
	wxString GetPath() const;
	wxString GetFileName() const;

protected:

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );
	
	OriginEnum		mOriginFrom;
	wxString		mOriginFileName;
	wxString		mOriginAdditional;
};

#endif // ORIGIN_H_INCLUDED
