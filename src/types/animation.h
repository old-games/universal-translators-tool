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

private:


	unsigned int	mFrames = 0;
	unsigned int	mWidth = 0;
	unsigned int	mHeight = 0;
};



#endif // __ANIMATION_H__