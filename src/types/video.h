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

private:
	
};


#endif // __VIDEO_H__
