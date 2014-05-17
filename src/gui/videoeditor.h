/***************************************************************
 * Name:      videoeditor.h
 * Purpose:   Video Editor
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-13
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/
#ifndef __VIDEO_EDITOR_H__
#define __VIDEO_EDITOR_H__

#include "uttpanelsgui.h"
#include "types/ieditor.h"
#include "panels/videopanel.h"
#include "taskqueue.h"



struct PlayerTask final
{
	enum Action
	{
		ptStop,
		ptPause,
		ptPlay,
		ptForward,
		ptBackward,
		ptJump
	};

	explicit PlayerTask(Action action, unsigned val = 0):
		mAction(action),
		mValue(val)
	{}

	PlayerTask(const PlayerTask& other):
		mAction(other.mAction),
		mValue(other.mValue)
	{
	}

	~PlayerTask()
	{
	}

	Action		mAction;
	unsigned	mValue;
};



//////////////////////////////////////////////////////////////////////////
/// VideoEditor



class VideoEditor: public VideoPanel, public IEditor,
	protected TaskManaged<PlayerTask>
{

public:

	VideoEditor( wxWindow* parent );
	virtual ~VideoEditor(void);


	// from IEditor
	virtual void Deinit() override;
	virtual bool SaveEditor() override;
	virtual bool LoadEditor() override;

	virtual bool SaveState( wxOutputStream& output ) override;
	virtual bool LoadState( wxInputStream& input, int version ) override;

	virtual OriginPtr GetOrigin() const override;
	virtual void SetInfo(IInfoPtr info) override;

protected:

	void PlayPressed();
	void PausePressed();
	void StopPressed();
	void BackwardPressed();
	void ForwardPressed();
	void PositionSlider(unsigned n);

private:

	void OnTimer(wxTimerEvent& event);

	void StartSound(bool b = true);
	void PlayThread();
	void PlayUpdate();
	void StopThread();
	void ShowCurrentFrame();
	void JumpToPosition(unsigned n);
	void OnSoundGetData();

	virtual bool CheckTasks() override;

	std::shared_ptr<std::thread> mThread;
	VideoPtr			mVideo;
	std::atomic<bool>	mPlayVideo = false;
	std::atomic<bool>	mPauseVideo = false;
	std::atomic<bool>	mGetNextFrame = false;
	std::mutex			mMutex;
	bool				mHasAudio = false;
	unsigned			mDelay = 0;
	unsigned			mLastFrame = 0;
	ImageInfoPtr		mCurrentImage;
	int					mCurrentFrame = -1;
	bool				mChunkedAudio = false;
	wxTimer				mTimer;
};




#endif // __VIDEO_EDITOR_H__


