/***************************************************************
 * Name:      undo.h
 * Purpose:   All for undo/redo
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-21
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef UTTUNDO_H_INCLUDED
#define UTTUNDO_H_INCLUDED

WX_DECLARE_OBJARRAY(wxEvtHandler*, EventHandlersArray);

// forward declarations
class EditPanel;
class ImageInfo;


class EventClient
{
	void		AddClient( wxEvtHandler* client );
	size_t		FindClient( wxEvtHandler* client );
	void		RemoveClient( wxEvtHandler* client );
	void		SendEvents( wxEvent* event );

	EventHandlersArray		mClients;
};



class PlacePixelCommand: public wxCommand
{
public:
	PlacePixelCommand( EditPanel* owner, const UttColour& oldValue, 
		const UttColour& newValue, const wxPoint& point );

    virtual bool Do();
    virtual bool Undo();

private:

	EditPanel*	mOwner;
	UttColour	mOldValue;
	UttColour	mNewValue;
	wxPoint		mPoint;
};



class ImagePasteCommand: public wxCommand
{
public:
	ImagePasteCommand( EditPanel* owner, ImageInfo* oldValue, 
		ImageInfo* newValue, const wxPoint& point );

	virtual ~ImagePasteCommand();

    virtual bool Do();
    virtual bool Undo();

private:

	EditPanel*	mOwner;
	ImageInfo*	mOldValue;
	ImageInfo*	mNewValue;
	wxPoint		mPoint;
};

#endif	// UTTUNDO_H_INCLUDED
