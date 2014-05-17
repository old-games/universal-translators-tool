#include "pch.h"
#include "animation.h"
#include "indexmask.h"



const wxString	ANIMNAME = "Animation";
const int		ANIMVERSION = 0x100;



Animation::Animation():
	IInfo( ANIMNAME, ANIMVERSION, etAnimation )
{
}



Animation::Animation(const Animation& other):
	IInfo(other),
	mFrames(other.mFrames),
	mWidth(other.mWidth),
	mHeight(other.mHeight),
	mCurrentFrame(other.mCurrentFrame),
	mDelay(other.mDelay),
	mIndexMask(other.mIndexMask ? other.mIndexMask->Clone() : other.mIndexMask)
{
}



/* virtual */ ImageInfoPtr Animation::GetFrame(unsigned)
{
	return nullptr;
}



/* virtual */ ImageInfoPtr Animation::GetNextFrame()
{
	if (IsLastFrame())
	{
		return GetCurrentFrame();
	}
	
	return GetFrame(mCurrentFrame++);
}



/* virtual */ ImageInfoPtr Animation::GetCurrentFrame()
{
	return GetFrame(mCurrentFrame);
}



bool Animation::IncFrame()
{
	if (mCurrentFrame < mFrames - 2)
	{
		++mCurrentFrame;
		return true;
	}

	return false;
}



/* virtual */ void Animation::SetCurrentFrame(unsigned frame)
{
	assert(frame < mFrames);
	mCurrentFrame = frame;
}




/* virtual */ void Animation::SetLastFrame()
{
	if (mFrames > 0)
	{
		mCurrentFrame = mFrames - 1;
	}
}


