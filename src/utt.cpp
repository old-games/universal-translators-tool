/***************************************************************
 * Name:      utt.cpp
 * Purpose:   Code for Application Class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-01-16
 * Copyright: Pavlovets Ilia
 * License:
 * Libs used: wxWidgets-last-svn,
 * Soft used: MS VS, Code::Blocks, GCC,
 **************************************************************/

#include "pch.h"
#include "utt.h"
#include "gui/mainframeimpl.h"
#include "luaconsole.h"
#include "panels/drawpanel.h"

IMPLEMENT_APP(UTTApp);



bool UTTApp::OnInit()
{
	// _CrtSetBreakAlloc ( 86092 );

	mCommandProcessor = new wxCommandProcessor();
	MainFrameImpl* frame = new MainFrameImpl();
#ifdef VISUALC
	//frame->SetIcon(wxICON(aaaa)); // To Set App Icon
#endif
	mConsoleFrame = new LuaConsole( frame );
	frame->Init();
	frame->Show();
    return true;
}


int UTTApp::OnExit()
{
	this->Unbind( wxEVT_KEY_DOWN, &UTTApp::OnKeyDown, this );
	mCommandProcessor->ClearCommands();
	delete mCommandProcessor;
	return wxApp::OnExit();
}


UTTApp::~UTTApp()
{
	DrawPanel::RefCheck();
}



void UTTApp::OnKeyDown( wxKeyEvent& event )
{
	switch ( event.GetKeyCode() )
	{
		case WXK_CONSOLE:
			ShowLuaConsole();
		break;

		default:
			event.Skip();
	}
}



void UTTApp::ShowLuaConsole()
{
	bool show = !mConsoleFrame->IsVisible();
	wxLogDebug( show ? "Show console" : "Hide console" );
	mConsoleFrame->Show( show );
}
