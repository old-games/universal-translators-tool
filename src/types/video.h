/***************************************************************
 * Name:      video.h
 * Purpose:   base video class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef __VIDEO_H__
#define __VIDEO_H__


#include "iinfo.h"


class Video: public IInfo
{
public:
	Video();
	Video(const Video& other);

	virtual ~Video() = default;

	VideoPtr Clone() const { return std::make_shared<Video>(*this); }

	void SetSound(SoundPtr snd);
	void SetAnimation(AnimationPtr anim);
	ImageInfoPtr GetNextFrame();
	ImageInfoPtr GetCurrentFrame();

	inline AnimationPtr GetAnimation() const { return mAnim; }
	inline SoundPtr GetSound() const { return mSound; }

	unsigned GetFrameNumber() const;

	bool IsLastFrame() const;
	void Backward();
	void Forward();

	inline void SetSoundPerFrame(bool b) { mSndPerFrame = b; }
	inline bool IsSoundPerFrame() const { return mSndPerFrame; }

private:

	AnimationPtr	mAnim;
	SoundPtr		mSound;
	bool			mSndPerFrame = false;
};


#endif // __VIDEO_H__
