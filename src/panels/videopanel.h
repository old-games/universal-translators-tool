#ifndef __VIDEO_PANEL_H__
#define __VIDEO_PANEL_H__


#include "gui/uttpanelsgui.h"


class DrawPanel;


class VideoPanel: public VideoPanelGui
{
public:

	enum Commands
	{
		cmPlay,
		cmStop,
		cmPause,
		cmBackward,
		cmForward,
		cmNum
	};

	VideoPanel(wxWindow* wnd, wxWindowID id = wxID_ANY);

	void SetCallback(Commands cmd, VoidCallback callback);
	void SetSliderCallback(UnsignedCallback callback);
	void SetPlayState(bool b);
	void SetFramesCount(unsigned frames);
	void SetSliderPosition(unsigned frame);
	void TurnButtons(bool b);

protected:

	void SetBitmap(wxBitmap* bmp);

private:

	virtual void OnButtonClick( wxCommandEvent& event ) override;
	virtual void OnSlider( wxScrollEvent& event ) override;

	void OnPlayPressed();
	void OnStopPressed();
	void OnForwardPressed();
	void OnBackwardPressed();
	void Call(Commands cmd);
	void UpdatePlayButtonState();

	DrawPanel*			mOutPanel = nullptr;
	VoidCallback		mCallbacks[cmNum];
	UnsignedCallback	mSliderCallback;
	bool				mPlaying = false;
};



#endif // __VIDEO_PANEL_H__