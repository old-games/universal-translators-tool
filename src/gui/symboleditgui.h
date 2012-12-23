/***************************************************************
 * Name:      symboleditgui.h
 * Purpose:   SymbolEditGui inherited from ImageEditor to use
				SymboPanel instead of EditPanel
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-14
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef SYMBOLEDITGUI_H_INCLUDED
#define SYMBOLEDITGUI_H_INCLUDED

#include "editpanelimpl.h"

class SymbolPanel;
class IndexMask;

class SymbolEditGui: public ImageEditor
{
public:
	SymbolEditGui( wxWindow* parent, wxWindowID eventsId );
	~SymbolEditGui(void);

	SymbolPanel* GetSymbolPanel()
	{
		return mSymbolPanel;
	}

	IndexMask* GetIndexMask();

private:

	SymbolPanel*	mSymbolPanel;

};

#endif
