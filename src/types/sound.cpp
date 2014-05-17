#include "pch.h"
#include "sound.h"
#include "soundbuffer.h"
#include "buffer.h"


const wxString	SOUNDNAME = "Sound";
const int		SOUNDVERSION = 0x100;



Sound::Sound():
	IInfo( SOUNDNAME, SOUNDVERSION, etSound)
{
}



Sound::Sound(unsigned int freq, unsigned int chan):
	IInfo( SOUNDNAME, SOUNDVERSION, etSound),
	mFreq(freq),
	mChans(chan),
	mBufIter(mBufs.begin()),
	mEndIter(mBufs.end())
{
	initialize(mChans, mFreq);
}



Sound::Sound(const Sound& other):
	IInfo(other)
{
}



Sound::~Sound()
{
	stop();
}



void Sound::AddBuffer(SoundBufferPtr buf)
{
	mBufs.push_back(buf);
	++mBufCount;
	mEndIter = mBufs.end();

	if (mFirstBuf)
	{
		mBufIter = mBufs.begin();
		mFirstBuf = false;
	}

	mTimeLength += buf->getDuration().asMilliseconds();
}



bool Sound::AddRawData(BufferPtr src, bool changeSign)
{
	SoundBufferPtr buf = Helpers::RawToSoundBuffer(src->GetData(),
		src->GetSize(), mChans, mFreq, changeSign ? 0x80 : 0);
	bool res = buf != nullptr;

	if (res)
	{
		AddBuffer(buf);
	}

	return res;
}



/* override */ bool Sound::onGetData(Chunk& data)
{
	if (mBufIter == mEndIter)
	{
		return false;
	}

	auto buf = *mBufIter;
	data.samples = buf->getSamples();
	data.sampleCount = buf->getSampleCount();
	++mBufIter;

	if (mOnGetDataCallback)
	{
		mOnGetDataCallback();
	}

	return true;
}



/* override */ void Sound::onSeek(sf::Time timeOffset)
{
	float f = (float) timeOffset.asMilliseconds() / (float) mTimeLength;
	mBufIter = mBufs.begin();
	size_t n = (size_t) (f * (float) mBufCount);
	std::advance(mBufIter, n);
}



void Sound::SeekToChunk(size_t n)
{
	float f = (float) n / (float) mBufCount;
	f *= (float) mTimeLength;
	setPlayingOffset(sf::milliseconds(f));
}



void Sound::SaveAsRaw(const std::string& filename)
{
	wxFileOutputStream output(filename);

	for (auto it: mBufs)
	{
		it->SaveRawData(output);
	}
}



