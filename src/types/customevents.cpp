/***************************************************************
 * Name:      custumevents.cpp
 * Purpose:   implementation of custom events
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
 
#include "pch.h"
#include "customevents.h"
#include "fontinfo.h"
wxDEFINE_EVENT( uttEVT_COLOURPICK, ColourPickEvent );
IMPLEMENT_DYNAMIC_CLASS(ColourPickEvent, wxEvent)


wxDEFINE_EVENT( uttEVT_CHANGEFONT, ChangeFontEvent );
IMPLEMENT_DYNAMIC_CLASS(ChangeFontEvent, wxEvent)

ChangeFontEvent::~ChangeFontEvent()
{
}


wxDEFINE_EVENT( uttEVT_CHANGEPALETTE, ChangePaletteEvent );
IMPLEMENT_DYNAMIC_CLASS(ChangePaletteEvent, wxEvent)


void ChangePaletteEvent::CopyPaletteData( void* src )
{
	wxASSERT( src != NULL );
	mSize = BPP::PaletteSize( mBPP );
	mData = malloc(mSize);
	memcpy( mData, src, mSize );
}


ChangePaletteEvent::~ChangePaletteEvent()
{
	if (mData)
	{
		free(mData);
	}
}