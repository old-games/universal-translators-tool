#include "pch.h"
#include "videopanel.h"
#include "drawpanel.h"
#include "icon/pause.xpm"
#include "icon/play.xpm"



VideoPanel::VideoPanel(wxWindow* wnd, wxWindowID id /* wxID_ANY */):
	VideoPanelGui(wnd, id)
{
	mOutPanel = new DrawPanel(this);
	mOutPanel->SetAlign(utdHCenter | utdVCenter | utdExpand);
	mVideoSizer->Add(mOutPanel, 1,
		wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5);
}



void VideoPanel::SetCallback(Commands cmd, VoidCallback callback)
{
	wxASSERT(cmd < cmNum);
	mCallbacks[cmd] = callback;
}



void VideoPanel::SetSliderCallback(UnsignedCallback callback)
{
	mSliderCallback = callback;
}



/* override */ void VideoPanel::OnButtonClick( wxCommandEvent& event )
{
	auto id = event.GetId();

	switch (id)
	{
		case wxID_PLAY_BTN:
			OnPlayPressed();
		break;

		case wxID_STOP_BTN:
			OnStopPressed();
		break;

		case wxID_FORWARD_BTN:
			OnForwardPressed();
		break;

		case wxID_BACKWARD_BTN:
			OnBackwardPressed();
		break;
	}

	event.Skip();
}



/* override */ void VideoPanel::OnSlider( wxScrollEvent& event )
{
	auto id = event.GetId();

	switch (id)
	{
		case wxID_VIDEO_SLIDER:
			if (mSliderCallback)
			{
				mSliderCallback(event.GetPosition());
			}
		break;
	}

	event.Skip();
}



inline void VideoPanel::Call(Commands cmd)
{
	if (mCallbacks[cmd])
	{
		mCallbacks[cmd]();
	}
}



void VideoPanel::OnPlayPressed()
{
	SetPlayState(!mPlaying);
	Call(mPlaying ? cmPlay : cmPause);
}



void VideoPanel::OnStopPressed()
{
	Call(cmStop);
	SetPlayState(false);
}



void VideoPanel::OnForwardPressed()
{
	Call(cmForward);
}



void VideoPanel::OnBackwardPressed()
{
	Call(cmBackward);
}




void VideoPanel::SetBitmap(wxBitmap* bmp)
{
	wxASSERT(mOutPanel);
	mOutPanel->SetBitmap(bmp);
}



inline void VideoPanel::UpdatePlayButtonState()
{
	mPlayBtn->SetBitmap(wxBitmap(mPlaying ? pause_xpm : play_xpm));
}



void VideoPanel::SetPlayState(bool b)
{
	mPlaying = b;
	UpdatePlayButtonState();
}



void VideoPanel::SetFramesCount(unsigned frames)
{
	mPosSlider->SetRange(0, frames - 1);
}



void VideoPanel::SetSliderPosition(unsigned frame)
{
	mPosSlider->SetValue(frame);
}



void VideoPanel::TurnButtons(bool b)
{
	mPlayBtn->Enable(b);
	mStopBtn->Enable(b);
	mForwardBtn->Enable(b);
	mBackBtn->Enable(b);
	mPosSlider->Enable(b);
}


