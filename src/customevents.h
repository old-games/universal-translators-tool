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
wxDECLARE_EVENT( uttEVT_COLOURPICK, ColourPickEvent );
wxDECLARE_EVENT( uttEVT_CHANGEFONT, ChangeFontEvent );

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



#endif  // CUSTOMEVENTS_H_INCLUDED
