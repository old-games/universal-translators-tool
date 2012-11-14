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

class ColourPickEvent;
class ChangeFontEvent;
class ChangePaletteEvent;

wxDECLARE_EVENT( uttEVT_COLOURPICK, ColourPickEvent );
wxDECLARE_EVENT( uttEVT_CHANGEFONT, ChangeFontEvent );
wxDECLARE_EVENT( uttEVT_CHANGEPALETTE, ChangePaletteEvent );

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
	{ }
	
    ColourPickEvent( const wxColour& colour, int button, ColourOperation what )
        : wxEvent(0, uttEVT_COLOURPICK),
			mColour( colour ),
			mButton( button ),
			mAction( what )
	{ }
	
    ColourPickEvent(const ColourPickEvent& event)
        : wxEvent(event),
   			mColour( event.mColour ),
			mButton( event.mButton ),
			mAction( event.mAction )
    { }

    virtual wxEvent *Clone() const { return new ColourPickEvent(*this); }
    
    int GetButton()
    {
		return mButton;
    }

	int GetAction()
	{
		return mAction;
	}
    
    const wxColour& GetColour()
    {
		return mColour;
    }

protected:
	
private:

	wxColour	mColour;
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

	~ChangeFontEvent();

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



class ChangePaletteEvent : public wxEvent
{
public:
	

    ChangePaletteEvent( )
        : wxEvent(0, uttEVT_CHANGEPALETTE),
		mBPP( -1 ),
		mData( NULL ),
		mSize( 0 ),
		mShiftLeft( false )
	{ 	
	}
	
    ChangePaletteEvent( int bpp, void* data, bool shift = false)
        : wxEvent(0, uttEVT_CHANGEPALETTE),
		mBPP( bpp ),
		mData( NULL ),
		mSize( 0 ),
		mShiftLeft( shift )
	{ 
		CopyPaletteData( data );
	}
	
    ChangePaletteEvent(const ChangePaletteEvent& event)
        : wxEvent(event),
		mBPP( event.mBPP ),
		mData( NULL ),
		mSize( event.mSize ),
		mShiftLeft( event.mShiftLeft )
    { 
		CopyPaletteData( event.mData );
	}

    virtual wxEvent *Clone() const { return new ChangePaletteEvent(*this); }
  
	int		GetBpp() { return mBPP; }
	void*	GetData() { return mData; }
	size_t	GetSize() { return mSize; }
	bool	ShiftValuesToLeft() { return mShiftLeft; }

	~ChangePaletteEvent();

protected:
	
private:

	void CopyPaletteData( void* src );

	int		mBPP;
	void*	mData;
	size_t	mSize;
	bool	mShiftLeft;

	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(ChangePaletteEvent)
};

typedef void (wxEvtHandler::*ChangePaletteEventFunction)(ChangePaletteEvent&);



#define ChangePaletteEventHandler(func) \
    wxEVENT_HANDLER_CAST(ChangePaletteEventFunction, func)

#define EVT_CHANGEPALETTE(func) wx__DECLARE_EVT0(uttEVT_CHANGEPALETTE, ChangePaletteEventHandler(func))



//////////////////////////////////////////////////////////////////////////



#endif  // CUSTOMEVENTS_H_INCLUDED
