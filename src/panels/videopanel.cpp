#include "pch.h"
#include "videopanel.h"
#include "drawpanel.h"




VideoPanel::VideoPanel(wxWindow* wnd, wxWindowID id /* wxID_ANY */):
	VideoPanelGui(wnd, id)
{
	mVideoPanel = new DrawPanel(this);
	mVideoSizer->Add(mVideoPanel, 1,
		wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5);
}



