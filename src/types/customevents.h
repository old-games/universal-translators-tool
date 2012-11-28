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

class ModuleChangedEvent;
class ColourPickEvent;
class ChangeFontEvent;
class ChangeImageEvent;
class ChangePaletteEvent;
class SymbolSelectionEvent;
class EditorRebuildDataEvent;



wxDECLARE_EVENT( uttEVT_MODULECHANGED, ModuleChangedEvent );
wxDECLARE_EVENT( uttEVT_COLOURPICK, ColourPickEvent );
wxDECLARE_EVENT( uttEVT_CHANGEFONT, ChangeFontEvent );
wxDECLARE_EVENT( uttEVT_CHANGEIMAGE, ChangeImageEvent );
wxDECLARE_EVENT( uttEVT_CHANGEPALETTE, ChangePaletteEvent );
wxDECLARE_EVENT( uttEVT_SYMBOLSELECT, SymbolSelectionEvent );
wxDECLARE_EVENT( uttEVT_REBUILDDATA, EditorRebuildDataEvent );


//////////////////////////////////////////////////////////////////////////



class ModuleChangedEvent : public wxEvent
{
public:
	
    ModuleChangedEvent( )
        : wxEvent(0, uttEVT_MODULECHANGED)
	{}
	
    ModuleChangedEvent(const ModuleChangedEvent& event)
        : wxEvent(event)
    {}

    virtual wxEvent *Clone() const { return new ModuleChangedEvent(*this); }

private:

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(ModuleChangedEvent)
};

typedef void (wxEvtHandler::*ModuleChangedEventFunction)(ModuleChangedEvent&);



#define ModuleChangedEventHandler(func) \
    wxEVENT_HANDLER_CAST(ModuleChangedEventFunction, func)

#define EVT_MODULECHANGED(func) wx__DECLARE_EVT0(uttEVT_MODULECHANGED, ModuleChangedEventHandler(func))



//////////////////////////////////////////////////////////////////////////



class ColourPickEvent : public wxEvent
{
public:
	
	enum ColourOperation
	{	
		cpeSetThisColour,
		cpeFindThisColour
	};

    ColourPickEvent( )
        : wxEvent(0, uttEVT_COLOURPICK),
			mColour( *wxBLACK ),
			mButton( 0 ),
			mAction( -1 )
	{ 
	
	}
	
    ColourPickEvent( const UttColour& colour, int button, ColourOperation what )
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


class FontInfo;

class ChangeFontEvent : public wxEvent
{
public:
	

    ChangeFontEvent( )
        : wxEvent(0, uttEVT_CHANGEFONT),
		mFontInfo( NULL )
	{ }
	
    ChangeFontEvent( FontInfo* fontInfo )
        : wxEvent(0, uttEVT_CHANGEFONT),
		mFontInfo( fontInfo )
	{ }
	
    ChangeFontEvent(const ChangeFontEvent& event)
        : wxEvent(event),
		mFontInfo( event.mFontInfo )
    { }

    virtual wxEvent *Clone() const { return new ChangeFontEvent(*this); }
    
    FontInfo*	GetFontInfo()
	{
		return mFontInfo;
	}

protected:
	
private:

	FontInfo*	mFontInfo;

	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(ChangeFontEvent)
};

typedef void (wxEvtHandler::*ChangeFontEventFunction)(ChangeFontEvent&);



#define ChangeFontEventHandler(func) \
    wxEVENT_HANDLER_CAST(ChangeFontEventFunction, func)

#define EVT_CHANGEFONT(func) wx__DECLARE_EVT0(uttEVT_CHANGEFONT, ChangeFontEventHandler(func))


//////////////////////////////////////////////////////////////////////////


class ImageInfo;

class ChangeImageEvent : public wxEvent
{
public:
	

    ChangeImageEvent( )
        : wxEvent(0, uttEVT_CHANGEIMAGE),
		mImageInfo( NULL )
	{ }
	
    ChangeImageEvent( ImageInfo* imageInfo )
        : wxEvent(0, uttEVT_CHANGEIMAGE),
		mImageInfo( imageInfo )
	{ }
	
    ChangeImageEvent(const ChangeImageEvent& event)
        : wxEvent(event),
		mImageInfo( event.mImageInfo )
    { }

    virtual wxEvent *Clone() const { return new ChangeImageEvent(*this); }
    
    ImageInfo*	GetImageInfo()
	{
		return mImageInfo;
	}

protected:
	
private:

	ImageInfo*	mImageInfo;

	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(ChangeImageEvent)
};

typedef void (wxEvtHandler::*ChangeImageEventFunction)(ChangeImageEvent&);

#define ChangeImageEventHandler(func) \
    wxEVENT_HANDLER_CAST(ChangeImageEventFunction, func)

#define EVT_CHANGEIMAGE(func) wx__DECLARE_EVT0(uttEVT_CHANGEIMAGE, ChangeImageEventHandler(func))



//////////////////////////////////////////////////////////////////////////



class Palette;

class ChangePaletteEvent : public wxEvent
{
public:
	

    ChangePaletteEvent( )
        : wxEvent(0, uttEVT_CHANGEPALETTE),
		mData( NULL ),
		mLock( false )
	{ 	
	}
	


    ChangePaletteEvent( int winid, Palette* pal, bool lockPal  )
        : wxEvent(winid, uttEVT_CHANGEPALETTE),
		mData( pal ),
		mLock( lockPal )
	{ 
	}
	
    ChangePaletteEvent(const ChangePaletteEvent& event)
        : wxEvent(event),
		mData( event.mData ),
		mLock( event.mLock )
    { 
	}

    virtual wxEvent *Clone() const { return new ChangePaletteEvent(*this); }
  
	Palette*	GetPalette() { return mData; }
	bool		GetLock() { return mLock; }

protected:
	
private:

	Palette*	mData;
	bool		mLock;

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
	

    SymbolSelectionEvent( )
        : wxEvent(0, uttEVT_SYMBOLSELECT),
		mKey( -1 )
	{ 	
	}
	


    SymbolSelectionEvent(int key )
        : wxEvent(0, uttEVT_SYMBOLSELECT),
		mKey( key )
	{ 
	}
	
    SymbolSelectionEvent(const SymbolSelectionEvent& event)
        : wxEvent(event),
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
		whPaletteChanged,
		whNum
	};

    EditorRebuildDataEvent( )
        : wxEvent(0, uttEVT_REBUILDDATA),
		mWhat( whNum )
	{ 	
	}
	


    EditorRebuildDataEvent( int winid, WhatHappend what, void* data = NULL )
        : wxEvent(winid, uttEVT_REBUILDDATA),
		mWhat( what ),
		mData( data )
	{ 
	}
	
    EditorRebuildDataEvent(const EditorRebuildDataEvent& event)
        : wxEvent(event),
		mWhat( event.mWhat ),
		mData( event.mData )
    { 
	}

    virtual wxEvent *Clone() const { return new EditorRebuildDataEvent(*this); }
  
	int			GetWhat() { return mWhat; }
	Palette*	GetPalette();

protected:
	
private:

	WhatHappend		mWhat;
	void*			mData;

	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(EditorRebuildDataEvent)
};

typedef void (wxEvtHandler::*EditorRebuildDataEventFunction)(EditorRebuildDataEvent&);



#define EditorRebuildDataEventHandler(func) \
    wxEVENT_HANDLER_CAST(EditorRebuildDataEventFunction, func)

#define EVT_REBUILDDATA(func) wx__DECLARE_EVT0(uttEVT_REBUILDDATA, EditorRebuildDataEventHandler(func))




#endif  // CUSTOMEVENTS_H_INCLUDED
