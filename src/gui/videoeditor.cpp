/***************************************************************
 * Name:      videoeditor.cpp
 * Purpose:   Video editor
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-13
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/



#include "pch.h"
#include "videoeditor.h"
#include "types/video.h"
#include "types/animation.h"
#include "types/imageinfo.h"
#include "types/sound.h"


#define LOCK std::lock_guard<std::mutex> lock(mMutex);
#define TIMER_UPDATE 25



VideoEditor::VideoEditor( wxWindow* parent ):
	VideoPanel(parent),
	IEditor( this, etVideo, "Video editor" )
{
	SetCallback(cmPlay, std::bind(&VideoEditor::PlayPressed, this));
	SetCallback(cmPause, std::bind(&VideoEditor::PausePressed, this));
	SetCallback(cmStop, std::bind(&VideoEditor::StopPressed, this));
	SetCallback(cmForward, std::bind(&VideoEditor::ForwardPressed, this));
	SetCallback(cmBackward, std::bind(&VideoEditor::BackwardPressed, this));
	SetSliderCallback(std::bind(&VideoEditor::PositionSlider, this,
		std::placeholders::_1));
	TurnButtons(false);
	mTimer.Bind(wxEVT_TIMER, &VideoEditor::OnTimer, this);
}



VideoEditor::~VideoEditor(void)
{
}



/* override */ void VideoEditor::Deinit()
{
	//StopPressed();

	//if (mThread)
	//{
	//	mThread->join();
	//}
	StopThread();
}




/* override */ bool VideoEditor::SaveEditor()
{
	return true;
}



/* override */ bool VideoEditor::LoadEditor()
{
	return true;
}



/* override */ bool VideoEditor::SaveState( wxOutputStream& /*output*/ )
{
	return true;
}



/* override */ bool VideoEditor::LoadState( wxInputStream& /*input*/, int /*version*/ )
{
	return true;
}



/* override */ OriginPtr VideoEditor::GetOrigin() const
{
	return mVideo ? mVideo->GetOrigin() : nullptr;
}



/* override */ void VideoEditor::SetInfo( IInfoPtr info )
{
	TurnButtons(false);

	if (mPlayVideo)
	{
		StopThread();
	}

	if (!info)
	{
		mVideo = nullptr;
		return;
	}

	mVideo = std::static_pointer_cast<Video>(info);

	if (!mVideo->GetAnimation())
	{
		wxLogError("VideoEditor::SetInfo error: no animation data in video");
		mVideo = nullptr;
		return;
	}

	auto snd = mVideo->GetSound();

	if (snd)
	{
		mHasAudio = true;
		mChunkedAudio = mVideo->IsSoundPerFrame();
		
		if (mChunkedAudio)
		{
			snd->SetOnGetDataCallback(std::bind(&VideoEditor::OnSoundGetData, this));
		}
	}
	this->SetFramesCount(mVideo->GetAnimation()->GetFramesCount());
	ShowCurrentFrame();
	TurnButtons(true);
	mDelay = mVideo->GetAnimation()->GetDelay();
	mLastFrame = mVideo->GetAnimation()->GetFramesCount() - 1;
}



void VideoEditor::PlayPressed()
{
	if (!mVideo)
	{
		return;
	}

	if (mPlayVideo)
	{
		AddTask(PlayerTask(PlayerTask::ptPlay));
		return;
	}

	StopThread();
	ClearTasks();
	mPlayVideo = true;
	mPauseVideo = false;
	mThread = std::make_shared<std::thread>(&VideoEditor::PlayThread, this);
	mTimer.Start(TIMER_UPDATE);

	if (mChunkedAudio)
	{
		mVideo->GetSound()->SeekToChunk(mVideo->GetFrameNumber());
	}
	else
	{
		StartSound();
	}
}



void VideoEditor::StartSound(bool b /* true */)
{
	auto snd = mVideo->GetSound();

	if (snd)
	{
		if (b)
		{
			snd->play();
		}
		else
		{
			snd->stop();
		}
	}
}


void VideoEditor::PausePressed()
{
	AddTask(PlayerTask(PlayerTask::ptPause));
}



void VideoEditor::StopPressed()
{
	if (mPlayVideo)
	{
		AddTask(PlayerTask(PlayerTask::ptStop));
	}
	else
	{
		BackwardPressed();
	}
}



void VideoEditor::StopThread()
{
	{
		LOCK
		mPlayVideo = false;
	}

	if (mThread)
	{
		mThread->join();
	}

	mThread = nullptr;
}


void VideoEditor::BackwardPressed()
{
	if (mPlayVideo)
	{
		AddTask(PlayerTask(PlayerTask::ptBackward));
	}
	else
	{
		JumpToPosition(0);
		ShowCurrentFrame();
		StartSound(false);
	}
}



void VideoEditor::ForwardPressed()
{
	if (mPlayVideo)
	{
		AddTask(PlayerTask(PlayerTask::ptForward));
	}
	else
	{
		JumpToPosition(mLastFrame);
		ShowCurrentFrame();
		StartSound(false);
	}
}



void VideoEditor::PositionSlider(unsigned n)
{
	if (mPlayVideo)
	{
		AddTask(PlayerTask(PlayerTask::ptJump, n));
	}
	else
	{
		JumpToPosition(n);
		ShowCurrentFrame();
	}
}



inline void VideoEditor::ShowCurrentFrame()
{
	if (mVideo)
	{
		auto img = mVideo->GetCurrentFrame();
	
		if (img)
		{
			SetBitmap(img->GetBitmap());
		}

		SetSliderPosition(mVideo->GetFrameNumber());
	}
}



void VideoEditor::PlayThread()
{
	while (mPlayVideo)
	{
		CheckTasks();
		PlayUpdate();

		if (mPauseVideo)
		{
			PAUSE(10);
		}
	}

//	wxLogMessage("Thread out!");
}



void VideoEditor::OnSoundGetData()
{
	mGetNextFrame = true;
}



void VideoEditor::PlayUpdate()
{
	if (!mPauseVideo)
	{
		{
			LOCK
			mCurrentFrame = mVideo->GetFrameNumber();

			if (mChunkedAudio && !mGetNextFrame)
			{
				PAUSE(5);
				return;
			}

			mGetNextFrame = false;
			mCurrentImage = mVideo->GetNextFrame();

			if (!mChunkedAudio)
			{
				PAUSE(mDelay);
			}
		}
	}
	else
	{
		LOCK
		mCurrentImage = mVideo->GetCurrentFrame();
	}
}




/* override */ bool VideoEditor::CheckTasks()
{
	if (IsTaskQueueEmpty())
	{
		return false;
	}

	bool wasJump = false;
	unsigned jump = 0;
	auto snd = mVideo->GetSound();

	while (!IsTaskQueueEmpty())
	{
		PlayerTask task = PopTask();

		switch (task.mAction)
		{
			case PlayerTask::ptPause:
				mPauseVideo = true;
				mCurrentFrame = mVideo->GetFrameNumber();

				if (mHasAudio)
				{
					snd->stop();
				}
			break;

			case PlayerTask::ptPlay:
				mPauseVideo = false;

				if (mHasAudio)
				{
					snd->SeekToChunk(mVideo->GetFrameNumber());
				}
			break;

			case PlayerTask::ptStop:
				mPlayVideo = false;
				mCurrentFrame = 0;
				JumpToPosition(0);
				StartSound(false);
			break;

			case PlayerTask::ptForward:
				wasJump = true;
				jump = mLastFrame;
			break;

			case PlayerTask::ptBackward:
				wasJump = true;
				jump = 0;
			break;

			case PlayerTask::ptJump:
				wasJump = true;
				jump = task.mValue;
			break;
		}
	}

	if (mPlayVideo && wasJump)
	{
		JumpToPosition(jump);
	}

	return true;
}



void VideoEditor::JumpToPosition(unsigned n)
{
	mVideo->GetAnimation()->SetCurrentFrame(n);
	auto snd = mVideo->GetSound();

	if (snd)
	{
		if (mChunkedAudio)
		{
			snd->SeekToChunk(n);
			
			if (!mPlayVideo || mPauseVideo)
			{
				snd->stop();
			}
		}
	}
}


// I know this looks stupid and ugly. But we can't update panel from thread otherwise
// it will deadlock on menu command "Close project" and on click at "X" to
// close app.
// And we can't use OnIdle event - there will be huge lags if app is no paused.
void VideoEditor::OnTimer(wxTimerEvent& event)
{
	{
		LOCK

		if (mCurrentImage)
		{
			SetBitmap(mCurrentImage->GetBitmap());
			mCurrentImage = nullptr;
		}

		if ((int) mCurrentFrame >= 0)
		{
			SetSliderPosition(mCurrentFrame);

			if (mCurrentFrame >= (int) mLastFrame)
			{
				SetPlayState(false);
				mPlayVideo = false;
			}

			mCurrentFrame = -1;
		}
	}

	if (mHasAudio)
	{
		LOCK

		if (mChunkedAudio && mVideo->GetSound()->IsStopped())
		{
			SetPlayState(false);
			SetSliderPosition(mLastFrame);
			mPlayVideo = false;
		}
	}

	if (!mPlayVideo)
	{
		mTimer.Stop();
	}

	event.Skip();
}


