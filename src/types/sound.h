/***************************************************************
 * Name:      sound.h
 * Purpose:   base sound class
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#ifndef __SOUND_H__
#define __SOUND_H__



#include "iinfo.h"
//#include "SFML/Audio/SoundStream.hpp"

class Sound: public IInfo, public sf::SoundStream
{
	struct ChunkData: Chunk
	{
		
	};

public:

	Sound();
	Sound(unsigned int freq, unsigned int chan);
	Sound(const Sound& other);
	
	virtual ~Sound();

	SoundPtr Clone() const { return std::make_shared<Sound>(*this); }

	bool AddRawData(BufferPtr src, bool changeSign);
	void SaveAsRaw(const std::string& filename);
	inline void SetOnGetDataCallback(VoidCallback callback)
		{ mOnGetDataCallback = callback; }
	void SeekToChunk(size_t n);
	
	inline bool IsPlaying() const { return getStatus() == sf::SoundSource::Playing; }
	inline bool IsStopped() const { return getStatus() == sf::SoundSource::Stopped; }

private:

	virtual bool onGetData(Chunk& data) override;
	virtual void onSeek(sf::Time timeOffset) override;
	void AddBuffer(SoundBufferPtr buf);

	
	unsigned int			mFreq = 0;
	unsigned int			mChans = 0;
	typedef std::list<SoundBufferPtr> BufferList;
	BufferList				mBufs;
	BufferList::iterator	mBufIter;
	BufferList::iterator	mEndIter;
	VoidCallback			mOnGetDataCallback;
	bool					mFirstBuf = true;
	size_t					mTimeLength = 0;
	size_t					mBufCount = 0; // std::list size() is slow
	sf::Sound				mCurrent;
	sf::Sound				mNext;
};



#endif // __SOUND_H__