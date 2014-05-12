#include "pch.h"
#include "video.h"



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

