/***************************************************************
 * Name:      animation.h
 * Purpose:   base animation class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef __ANIMATION_H__
#define __ANIMATION_H__



#include "iinfo.h"


class Animation: public IInfo
{
public:

	Animation();
	Animation(const Animation& other);
	
	virtual ~Animation() = default;
	AnimationPtr Clone() const { return std::make_shared<Animation>(*this); }

	inline unsigned int GetFramesCount() const { return mFrames; }
	inline unsigned int GetDelay() const { return mDelay; }
	inline bool IsLastFrame() const { return mCurrentFrame == mFrames - 1; }
	inline unsigned int GetFrameNumber() const { return mCurrentFrame; }

	virtual ImageInfoPtr GetFrame(unsigned frame);
	virtual ImageInfoPtr GetNextFrame();
	virtual ImageInfoPtr GetCurrentFrame();
	bool IncFrame();
	virtual void SetCurrentFrame(unsigned frame);
	void SetLastFrame();

protected:

	unsigned int	mFrames = 0;
	unsigned int	mWidth = 0;
	unsigned int	mHeight = 0;
	unsigned int	mCurrentFrame = 0;
	unsigned int	mDelay = 0;
	IndexMaskPtr	mIndexMask;
};



#endif // __ANIMATION_H__