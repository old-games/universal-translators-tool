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

	virtual int CheckChanged();
	virtual bool SaveEditor() = 0; 

protected:


private:

	wxWindow*	mParent;
	EditorType	mEditorType;
	bool		mChanged;
	wxString	mEditorName;
};



WX_DEFINE_ARRAY( IEditor* , EditorsArray );
typedef EditorsArray::iterator EditorsIterator;



#endif // PROJECT_H_INCLUDED
