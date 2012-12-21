/***************************************************************
 * Name:      undo.cpp
 * Purpose:   All for undo/redo
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-11-21
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "undo.h"
#include "customevents.h"
#include "imageinfo.h"
#include "panels/editpanel.h"
#include <wx/arrimpl.cpp>

WX_DEFINE_OBJARRAY(EventHandlersArray);



void EventClient::AddClient( wxEvtHandler* client )
{
	if ( FindClient(client) < mClients.size() )
	{
		mClients.Add(client);
	}
	else
	{
		wxLogWarning( wxString::Format("Eventhandler (%X) in list already!", client) );
	}
}



size_t EventClient::FindClient( wxEvtHandler* client )
{
	for (size_t i = 0; i < mClients.size(); ++i)
	{
		if (mClients[i] == client)
			return i;
	}
	return (size_t) -1;	// 0xFFFFFFFF
}



void EventClient::RemoveClient( wxEvtHandler* client )
{
	size_t i = FindClient( client );
	if (i < mClients.size())
	{
		mClients.RemoveAt(i);
	}
}



void EventClient::SendEvents( wxEvent* event )
{
	for (size_t i = 0; i < mClients.size(); ++i)
	{
		mClients[i]->QueueEvent( event );
	}
}



//////////////////////////////////////////////////////////////////////////



PlacePixelCommand::PlacePixelCommand( EditPanel* owner, const UttColour& oldValue, 
									 const UttColour& newValue, const wxPoint& point ): 
	wxCommand(true, "PlacePixelCommand"),
	mOwner( owner ),
	mOldValue( oldValue ),
	mNewValue( newValue ),
	mPoint( point )
{
}



/* virtual */ bool PlacePixelCommand::Do()
{
	return mOwner->DoPlacePixel( mPoint, mNewValue );
}



/* virtual */ bool PlacePixelCommand::Undo()
{
	return mOwner->DoPlacePixel( mPoint, mOldValue );
}



//////////////////////////////////////////////////////////////////////////



ImagePasteCommand::ImagePasteCommand( EditPanel* owner, ImageInfo* oldValue, 
								ImageInfo* newValue, const wxPoint& point ): 
	wxCommand(true, "ImagePasteCommand"),
	mOwner( owner ),
	mOldValue( oldValue ),
	mNewValue( newValue ),
	mPoint( point )
{
}



ImagePasteCommand::~ImagePasteCommand()
{
	delete mOldValue;
	delete mNewValue;
}



/* virtual */ bool ImagePasteCommand::Do()
{
	mOwner->DoPaste( mPoint, mNewValue );
	return true;
}



/* virtual */ bool ImagePasteCommand::Undo()
{
	mOwner->DoPaste( mPoint, mOldValue );
	return true;
}

