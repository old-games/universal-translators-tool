/***************************************************************
 * Name:      symboleditgui.cpp
 * Purpose:   Code for SymbolEditGui class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-03-14
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"

#include "symboleditgui.h"
#include "panels/symbolpanel.h"
#include "types/imageinfo.h"



SymbolEditGui::SymbolEditGui(  wxWindow* parent, wxWindowID eventsId ):
	ImageEditor( parent, eventsId ),
	mSymbolPanel( new SymbolPanel( this, eventsId ) )
{
	ImageEditor::SetEditPanel( mSymbolPanel );
	mSymbolPanel->SetScaleRange( 1.0f, 50.0f );
}



SymbolEditGui::~SymbolEditGui(void)
{
}



IndexMask* SymbolEditGui::GetIndexMask()
{
	IndexMask* res = NULL;

	if ( mSymbolPanel->GetImageInfo()->IsOk() )
	{
		res = mSymbolPanel->GetImageInfo()->GetImage();
	}

	return res;
}