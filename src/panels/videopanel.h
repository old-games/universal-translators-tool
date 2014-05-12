#ifndef __VIDEO_PANEL_H__
#define __VIDEO_PANEL_H__


#include "gui/uttpanelsgui.h"


class DrawPanel;


class VideoPanel: public VideoPanelGui
{
public:
	VideoPanel(wxWindow* wnd, wxWindowID id = wxID_ANY);

private:


	DrawPanel*		mVideoPanel = nullptr;
};



#endif // __VIDEO_PANEL_H__