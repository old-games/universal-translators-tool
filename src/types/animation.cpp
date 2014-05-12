#include "pch.h"
#include "animation.h"


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
	mHeight(other.mHeight)
{
}

