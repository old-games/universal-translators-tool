/***************************************************************
 * Name:      custumevents.h
 * Purpose:   custom events for internal use
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef CUSTOMEVENTS_H_INCLUDED
#define CUSTOMEVENTS_H_INCLUDED

#include "types/uttypes.h"
#include "types/iinfo.h"

class CommonEvent;
class ColourPickEvent;
class ChangeInfoEvent;
class ChangePaletteEvent;
class SymbolSelectionEvent;
class EditorRebuildDataEvent;
class AUIWindowEvent;
class IEditor;



wxDECLARE_EVENT( uttEVT_COMMON, CommonEvent );
wxDECLARE_EVENT( uttEVT_COLOURPICK, ColourPickEvent );
wxDECLARE_EVENT( uttEVT_CHANGEINFO, ChangeInfoEvent );
wxDECLARE_EVENT( uttEVT_CHANGEPALETTE, ChangePaletteEvent );
wxDECLARE_EVENT( uttEVT_SYMBOLSELECT, SymbolSelectionEvent );
wxDECLARE_EVENT( uttEVT_REBUILDDATA, EditorRebuildDataEvent );
wxDECLARE_EVENT( uttEVT_ADDAUIWINDOW, AUIWindowEvent );



//////////////////////////////////////////////////////////////////////////



class CommonEvent : public wxEvent
{
public:
	
	enum CommoneEventOperation
	{	
		ceModuleChanged,
		ceSetProjectName,
		ceSetProjectPath,
		ceSetProjectModule,
	};
	
	CommonEvent(): wxEvent(0, uttEVT_COMMON),
		mAction(ceModuleChanged)
	{}

	CommonEvent(CommoneEventOperation what): wxEvent(0, uttEVT_COMMON),
		mAction(what)
	{}

	CommonEvent(const CommonEvent& event): wxEvent(event),
		mAction(event.mAction),
		mParams(event.mParams)
	{}

	virtual wxEvent *Clone() const { return new CommonEvent(*this); }

	int GetAction()
	{
		return mAction;
	}

	void AddParam(const wxString& value)
	{
		mParams.Add(value);
	}

	const wxArrayString& GetParams() const
	{
		return mParams;
	}

private:
	
	CommoneEventOperation	mAction;
	wxArrayString			mParams;

	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(CommonEvent)
};

typedef void (wxEvtHandler::*CommonEventFunction)(CommonEvent&);



#define CommonEventHandler(func) \
	wxEVENT_HANDLER_CAST(CommonEventFunction, func)

#define EVT_COMMON(func) wx__DECLARE_EVT0(uttEVT_COMMON, CommonEventHandler(func))



//////////////////////////////////////////////////////////////////////////



class ColourPickEvent : public wxEvent
{
public:
	
	enum ColourOperation
	{	
		cpeSetThisColour,
		cpeFindThisColour
	};

	ColourPickEvent()
		: wxEvent(0, uttEVT_COLOURPICK),
			mColour( *wxBLACK ),
			mButton( 0 ),
			mAction( -1 )
	{
	}
	
	ColourPickEvent(const UttColour& colour, int button, ColourOperation what)
		: wxEvent(0, uttEVT_COLOURPICK),
			mColour( colour ),
			mButton( button ),
			mAction( what )
	{ 
	
	}
	
	ColourPickEvent(const ColourPickEvent& event)
		: wxEvent(event),
			mColour( event.mColour ),
			mButton( event.mButton ),
			mAction( event.mAction )
	{ 

	}

	virtual wxEvent *Clone() const { return new ColourPickEvent(*this); }

	int GetButton()
	{
		return mButton;
	}

	int GetAction()
	{
		return mAction;
	}

	const UttColour& GetColour()
	{
		return mColour;
	}

protected:
	
private:

	UttColour	mColour;
	int			mButton;
	int			mAction;
	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(ColourPickEvent)
};

typedef void (wxEvtHandler::*ColourPickEventFunction)(ColourPickEvent&);



#define ColourPickEventHandler(func) \
	wxEVENT_HANDLER_CAST(ColourPickEventFunction, func)

#define EVT_COLOURPICK(func) wx__DECLARE_EVT0(uttEVT_COLOURPICK, ColourPickEventHandler(func))


//////////////////////////////////////////////////////////////////////////



class ChangeInfoEvent : public wxEvent
{
public:
	

	ChangeInfoEvent(): wxEvent(0, uttEVT_CHANGEINFO),
		mInfo( NULL )
	{ }

	ChangeInfoEvent( IInfoPtr info, int winId = 0 ):
		wxEvent(winId, uttEVT_CHANGEINFO),
			mInfo( info )
	{ }

	ChangeInfoEvent(const ChangeInfoEvent& event): wxEvent(event),
		mInfo( event.mInfo )
	{ }

	virtual wxEvent *Clone() const { return new ChangeInfoEvent(*this); }
	IInfoPtr GetInfo() const { return mInfo; }

protected:
	
private:

	IInfoPtr	mInfo;

	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(ChangeInfoEvent)
};

typedef void (wxEvtHandler::*ChangeInfoEventFunction)(ChangeInfoEvent&);



#define ChangeInfoEventHandler(func) \
	wxEVENT_HANDLER_CAST(ChangeInfoEventFunction, func)

#define EVT_CHANGEINFO(func) wx__DECLARE_EVT0(uttEVT_CHANGEINFO, ChangeInfoEventHandler(func))



//////////////////////////////////////////////////////////////////////////



class ChangePaletteEvent : public wxEvent
{
public:
	

	ChangePaletteEvent():
		wxEvent(0, uttEVT_CHANGEPALETTE),
		mData( NULL ),
		mRebuild( false )
	{
	}
	


	ChangePaletteEvent( int winid, PalettePtr pal, bool rebuild ):
		wxEvent(winid, uttEVT_CHANGEPALETTE),
		mData( pal ),
		mRebuild( rebuild )
	{ 
	}
	
	ChangePaletteEvent(const ChangePaletteEvent& event): wxEvent(event),
		mData( event.mData ),
		mRebuild( event.mRebuild )
	{
	}

	virtual wxEvent *Clone() const { return new ChangePaletteEvent(*this); }

	inline PalettePtr	GetPalette() const { return mData; }
	inline bool		GetRebuild() const { return mRebuild; }

protected:
	
private:

	PalettePtr	mData;
	bool		mRebuild;

	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(ChangePaletteEvent)
};

typedef void (wxEvtHandler::*ChangePaletteEventFunction)(ChangePaletteEvent&);



#define ChangePaletteEventHandler(func) \
    wxEVENT_HANDLER_CAST(ChangePaletteEventFunction, func)

#define EVT_CHANGEPALETTE(func) wx__DECLARE_EVT0(uttEVT_CHANGEPALETTE, ChangePaletteEventHandler(func))



//////////////////////////////////////////////////////////////////////////



class SymbolSelectionEvent : public wxEvent
{
public:
	

	SymbolSelectionEvent( ):
		wxEvent(0, uttEVT_SYMBOLSELECT),
		mKey( -1 )
	{
	}

	SymbolSelectionEvent(int winid, int key ):
		wxEvent(winid, uttEVT_SYMBOLSELECT),
		mKey( key )
	{ 
	}
	
	SymbolSelectionEvent(const SymbolSelectionEvent& event):
		wxEvent(event),
		mKey( event.mKey )
	{
	}

	virtual wxEvent *Clone() const { return new SymbolSelectionEvent(*this); }
	int		GetKey() { return mKey; }

protected:
	
private:

	int		mKey;

	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(SymbolSelectionEvent)
};

typedef void (wxEvtHandler::*SymbolSelectionEventFunction)(SymbolSelectionEvent&);



#define SymbolSelectionEventHandler(func) \
	wxEVENT_HANDLER_CAST(SymbolSelectionEventFunction, func)

#define EVT_SYMBOLSELECT(func) wx__DECLARE_EVT0(uttEVT_SYMBOLSELECT, SymbolSelectionEventHandler(func))



//////////////////////////////////////////////////////////////////////////



class EditorRebuildDataEvent : public wxEvent
{
public:
	enum WhatHappend
	{
		whEditColourChanged,
		whPaletteChanged,
		whIndexMaskChanged,
		whEditorStateChanged,
		whNum
	};

	EditorRebuildDataEvent( ):
		wxEvent(0, uttEVT_REBUILDDATA),
			mWhat( whNum ),
			mData(nullptr),
			mBool( false )
	{
	}
	


	EditorRebuildDataEvent( int winid, WhatHappend what,
		void* data = NULL, bool additional = false ):
			wxEvent(winid, uttEVT_REBUILDDATA),
				mWhat( what ),
				mData( data ),
				mBool( additional )
	{
	}

	EditorRebuildDataEvent( int winid, PalettePtr pal, bool additional = false ):
			wxEvent(winid, uttEVT_REBUILDDATA),
				mWhat( whPaletteChanged ),
				mPalette( pal ),
				mBool( additional )
	{
	}
	
	EditorRebuildDataEvent(const EditorRebuildDataEvent& event):
		wxEvent(event),
			mWhat(event.mWhat),
			mData(event.mData),
			mPalette(event.mPalette),
			mBool(event.mBool)
	{
	}

	virtual wxEvent *Clone() const { return new EditorRebuildDataEvent(*this); }

	int			GetWhat() const { return mWhat; }
	PalettePtr	GetPalette() const;
	UttColour*	GetColour() const;
	IEditor*	GetEditor() const;
	bool		GetBool() { return mBool; }

protected:
	
private:

	WhatHappend		mWhat;
	void*			mData = nullptr;
	PalettePtr		mPalette;
	bool			mBool = false;

	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(EditorRebuildDataEvent)
};

typedef void (wxEvtHandler::*EditorRebuildDataEventFunction)(EditorRebuildDataEvent&);



#define EditorRebuildDataEventHandler(func) \
    wxEVENT_HANDLER_CAST(EditorRebuildDataEventFunction, func)

#define EVT_REBUILDDATA(func) wx__DECLARE_EVT0(uttEVT_REBUILDDATA, EditorRebuildDataEventHandler(func))



//////////////////////////////////////////////////////////////////////////



class AUIWindowEvent : public wxEvent
{
public:
	
	enum
	{
		AddWindow,
		RemoveWindow,
		RenameWindow,
		UpdateManager,
		ShowWindow,
		HideWindow,
		SetActive,
		AUIEventNum
	};

	AUIWindowEvent():
		wxEvent(0, uttEVT_ADDAUIWINDOW),
		mCommand( AUIEventNum ),
		mWindow( NULL ),
		mUpdate( false ),
		mName( wxEmptyString )
	{ 	
	}



	AUIWindowEvent(int command, wxWindow* wnd = NULL, bool doUpdate = true,
		const wxString& name = wxEmptyString):
			wxEvent(0, uttEVT_ADDAUIWINDOW),
			mCommand( command ),
			mWindow( wnd ),
			mUpdate( doUpdate || command == UpdateManager),
			mName( name )
	{
	}

	AUIWindowEvent(const AUIWindowEvent& event):
			wxEvent(event),
			mCommand( event.mCommand ),
			mWindow( event.mWindow ),
			mUpdate( event.mUpdate ),
			mName( event.mName )
	{
	}

	virtual wxEvent *Clone() const { return new AUIWindowEvent(*this); }

	int				GetCommand() const { return mCommand; }
	wxWindow*		GetWindow() const { return mWindow; }
	const wxString& GetName() const { return mName; }
	bool			DoUpdate() const { return mUpdate; }

protected:

private:

	int			mCommand;
	wxWindow*	mWindow;
	bool		mUpdate;
	wxString	mName;

	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(AUIWindowEvent)
};

typedef void (wxEvtHandler::*AddAUIWindowEventFunction)(AUIWindowEvent&);



#define AddAUIWindowEventHandler(func) \
	wxEVENT_HANDLER_CAST(AddAUIWindowEventFunction, func)

#define EVT_ADDAUIWINDOW(func) wx__DECLARE_EVT0(uttEVT_ADDAUIWINDOW, AddAUIWindowEventHandler(func))



//////////////////////////////////////////////////////////////////////////




#endif  // CUSTOMEVENTS_H_INCLUDED
