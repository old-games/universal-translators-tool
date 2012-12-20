/***************************************************************
 * Name:      ieditor.h
 * Purpose:   declaration of IEditor interface
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef IEDITOR_H_INCLUDED
#define IEDITOR_H_INCLUDED



enum EditorType
{
	etFont,
	etImage,
	etLibrary,
	etAnimation,
	etSound,
	etVideo,
	etNum
};

extern const wxString sEditorNames[ etNum ];

class IEditor
{
public:

	IEditor( wxWindow* parent, EditorType edtype, const wxString& name );
	IEditor( const IEditor& other );
	virtual ~IEditor();

	EditorType	GetType() const { return mEditorType; }
	int			GetEditorId() const { return mEditorId; }
	wxWindow*	GetWindow() const { return mParent; }
	wxString	CreateName();

	void SetEditorId( int id ) { mEditorId = id; }

	virtual int		CheckChanged();
	virtual bool	SaveEditor( wxOutputStream& output ) = 0; 
	virtual bool	LoadEditor( wxInputStream& input ) = 0; 

protected:


private:

	wxWindow*	mParent;
	EditorType	mEditorType;
	bool		mChanged;
	wxString	mEditorName;
	int			mEditorId;
};



WX_DEFINE_ARRAY( IEditor* , EditorsArray );
typedef EditorsArray::iterator EditorsIterator;



#endif // PROJECT_H_INCLUDED
