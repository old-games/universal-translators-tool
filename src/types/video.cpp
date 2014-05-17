#include "pch.h"
#include "video.h"
#include "animation.h"


const wxString	VIDEONAME = "Video";
const int		VIDEOVERSION = 0x100;



Video::Video():
	IInfo( VIDEONAME, VIDEOVERSION, etVideo)
{
}



Video::Video(const Video& other):
	IInfo(other)
{
}



void Video::SetAnimation(AnimationPtr anim)
{
	mAnim = anim;
}



void Video::SetSound(SoundPtr snd)
{
	mSound = snd;
}




ImageInfoPtr Video::GetNextFrame()
{
	assert(mAnim);
	return mAnim->GetNextFrame();
}


ImageInfoPtr Video::GetCurrentFrame()
{
	assert(mAnim);
	return mAnim->GetCurrentFrame();
}



unsigned Video::GetFrameNumber() const
{
	assert(mAnim);
	return mAnim->GetFrameNumber();
}



bool Video::IsLastFrame() const
{
	assert(mAnim);
	return mAnim->IsLastFrame();
}



void Video::Backward()
{
	mAnim->SetCurrentFrame(0);
}



void Video::Forward()
{
	mAnim->SetLastFrame();
}




