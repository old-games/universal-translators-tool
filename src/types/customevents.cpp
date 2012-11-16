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
#include "palette.h"



wxDEFINE_EVENT( uttEVT_MODULECHANGED, ModuleChangedEvent );
IMPLEMENT_DYNAMIC_CLASS(ModuleChangedEvent, wxEvent)



//////////////////////////////////////////////////////////////////////////



wxDEFINE_EVENT( uttEVT_COLOURPICK, ColourPickEvent );
IMPLEMENT_DYNAMIC_CLASS(ColourPickEvent, wxEvent)



//////////////////////////////////////////////////////////////////////////



wxDEFINE_EVENT( uttEVT_CHANGEFONT, ChangeFontEvent );
IMPLEMENT_DYNAMIC_CLASS(ChangeFontEvent, wxEvent)



//////////////////////////////////////////////////////////////////////////



wxDEFINE_EVENT( uttEVT_CHANGEPALETTE, ChangePaletteEvent );
IMPLEMENT_DYNAMIC_CLASS(ChangePaletteEvent, wxEvent)



//////////////////////////////////////////////////////////////////////////



wxDEFINE_EVENT( uttEVT_SYMBOLSELECT, SymbolSelectionEvent );
IMPLEMENT_DYNAMIC_CLASS(SymbolSelectionEvent, wxEvent)
