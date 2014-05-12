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


// forward declarations

class Origin;


extern const wxString sEditorNames[ etNum ];

class IEditor: public IStateStore
{
public:

	IEditor( wxWindow* parent, EditorType edtype, const wxString& name );
	IEditor( const IEditor& other );
	virtual ~IEditor();

	EditorType	GetType() const { return mEditorType; }
	int			GetEditorId() const { return mEditorId; }
	wxWindow*	GetWindow() const { return mParent; }
	void		Changed( bool b = true );
	bool		IsChanged() const { return mChanged; }
	wxString	CreateName();

	void CreateEditorId();
	void SetEditorId( int id ) { mEditorId = id; }

	virtual bool	CheckChanged();
	virtual bool	SaveEditor() = 0; 
	virtual bool	LoadEditor() = 0; 

	virtual void		SetInfo( IInfoPtr info ) = 0;
	virtual OriginPtr	GetOrigin() const = 0;

	static IEditor* CreateEditor( EditorType edType, bool createId = true  );
	static IEditor* CreateEditor( wxInputStream& input );
	static wxWindow* sParentWindow;	// hack window to create invisible panels

protected:

	virtual bool SaveState( wxOutputStream& output );
	virtual bool LoadState( wxInputStream& input, int version );

private:

	wxWindow*	mParent;
	EditorType	mEditorType;
	bool		mChanged;
	wxString	mEditorName;
	int			mEditorId;

};



WX_DEFINE_ARRAY( IEditor* , EditorsArray );
typedef EditorsArray::iterator EditorsIterator;
typedef EditorsArray::const_iterator ConstEditorsIterator;



#endif // PROJECT_H_INCLUDED
