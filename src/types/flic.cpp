#include "pch.h"
#include "flic.h"
#include "palette.h"
#include "algs/rle.h"
#include "indexmask.h"
#include "imageinfo.h"


//////////////////////////////////////////////////////////////////////////
/// FlicAnimation



FlicAnimation::FlicAnimation()
{
	mPalette = std::make_shared<Palette>();
	mPalette->Initiate(Palette::bpp8, (wxByte*) nullptr);
}



bool FlicAnimation::OpenFlicFile(const std::string& filename)
{
	mInputStream = std::make_shared<wxFileInputStream>(filename);
	bool res = false;
	
	if (mInputStream->IsOk())
	{
		mFilename = filename;
		wxBusyInfo info("Loading, please wait...");
		res = Open(*mInputStream);
	}

	if (!res)
	{
		mInputStream = nullptr;
	}
	return res;
}



bool FlicAnimation::Open(wxInputStream& stream)
{
	mLoadedChunks.clear();
	mCurrentFrame = 0;
	mFrames = 0;

	if (!mHeader.Load(stream) || !mHeader.IsSupported())
	{
		wxLogError("Not support FLIC file %s (ID) %X",
			mFilename, mHeader.GetType());
		return false;
	}

	while (stream.CanRead())
	{
		wxUint32 chunkSize = 0;
		wxUint16 chunkType = 0;

		if (!IStateStore::LoadSimpleType(stream, chunkSize) ||
			!IStateStore::LoadSimpleType(stream, chunkType))
		{
			if (stream.GetLastError() == wxSTREAM_EOF)
			{
				break;
			}

			wxLogError("Can't read chunk info in %s %d %X",
				mFilename, chunkSize, chunkType);
			return false;
		}

		if (!LoadChunk(stream, chunkType, chunkSize))
		{
			return false;
		}
	}

	mWidth = mHeader.GetWidth();
	mHeight = mHeader.GetHeight();
	mDelay = mHeader.GetSpeed();
	mFrames = mLoadedChunks[FRAME].size();
	mIndexMask = std::make_shared<IndexMask>();
	mIndexMask->InitMask(mWidth, mHeight);
	return true;
}



bool FlicAnimation::LoadChunk(wxInputStream& stream, wxUint16 chunkType, wxUint32 size)
{
	FlicChunk::Ptr chunk;

	switch (chunkType)
	{
		case PREFIX:
			chunk = std::make_shared<PrefixChunk>(chunkType, size);
		break;

		case FRAME:
			chunk = std::make_shared<FrameChunk>(chunkType, size);
		break;

		default:
			chunk = CreateDynamicChunk(chunkType, size);

			if (!chunk)
			{
				wxLogMessage("FlicAnimation::LoadChunk error: unknown chunk %X, size %d",
					chunkType, size);
			}
	}

	if (chunk)
	{
		chunk->LoadHeader(stream);
		//chunk->PrintInfo();
		mLoadedChunks[chunkType].push_back(chunk);
	}

	return chunk != nullptr;
}



void FlicAnimation::AddDynamicChunk(wxUint16 type, DynamicFlicChunk::Ptr chunk)
{
	wxASSERT(chunk);
	mDynamicChunks[type] = chunk;
}



size_t FlicAnimation::GetChunksCount(wxUint16 type) const
{
	auto it = mLoadedChunks.find(type);
	return it == mLoadedChunks.end() ? 0 : it->second.size();
}



FlicChunk::Ptr FlicAnimation::GetChunk(wxUint16 type, size_t n) const
{
	auto it = mLoadedChunks.find(type);
	assert(it != mLoadedChunks.end());
	auto& list = it->second;
	assert(n < list.size());
	auto chunk_it = list.begin();
	std::advance(chunk_it, n);
	return *chunk_it;
}



DynamicFlicChunk::Ptr FlicAnimation::GetDynamicChunk(wxUint16 type, size_t n) const
{
	auto res = GetChunk(type, n);
	return std::static_pointer_cast<DynamicFlicChunk>(res);
}



FlicChunk::Ptr FlicAnimation::CreateDynamicChunk(wxUint16 chunkType, wxUint32 size)
{
	FlicChunk::Ptr result;
	auto it = mDynamicChunks.find(chunkType);

	if (it == mDynamicChunks.end())
	{
		return result;
	}

	result = it->second->Clone(chunkType, size);
	return result;
}



inline ImageDataChunk::Ptr FlicAnimation::CheckImageChunk(FrameChunk::Ptr chunk) const
{
	if (chunk->HasChunk(DELTA_FLC))
	{
		return chunk->GetSubchunk<ImageDataChunk>(DELTA_FLC);
	}
	else if (chunk->HasChunk(FLI_COPY))
	{
		return chunk->GetSubchunk<ImageDataChunk>(FLI_COPY);
	}
	else if (chunk->HasChunk(FLI_BRUN))
	{
		return chunk->GetSubchunk<ImageDataChunk>(FLI_BRUN);
	}
	else if (chunk->HasChunk(DELTA_FLI))
	{
		return chunk->GetSubchunk<ImageDataChunk>(DELTA_FLI);
	}

	return nullptr;
}



/* override */ ImageInfoPtr FlicAnimation::GetFrame(unsigned frame)
{
	wxASSERT(frame < mFrames);

	ImageInfoPtr result;
	auto& list = mLoadedChunks[FRAME];
	auto it = list.begin();
	std::advance(it, frame);
	auto chunk = std::static_pointer_cast<FrameChunk>(*it);

	if (chunk->HasChunk(PAL))
	{
		auto pal = chunk->GetSubchunk<PaletteChunk>(PAL);
		
		if (pal->LoadData(*mInputStream))
		{
			pal->ApplyToPalette(mPalette);
		}
	}

	auto img = CheckImageChunk(chunk);

	if (img && img->LoadData(*mInputStream))
	{
		switch (img->GetType())
		{
			case FLI_BRUN:
			{
				UnpackFLIByteRun(mIndexMask->GetMaskForWriting(), img->GetData(), mWidth, mHeight);
			}
			break;

			case DELTA_FLC:
				UnpackFLCDelta(mIndexMask->GetMaskForWriting(), img->GetData(), mWidth);
			break;

			case FLI_COPY:
				memcpy(mIndexMask->GetMaskForWriting(), img->GetData(), mWidth * mHeight);
			break;

			case DELTA_FLI:
			default:
				wxLogError("Not ready yet!");
				assert(false);
		}

		result = std::make_shared<ImageInfo>(mIndexMask, mPalette);
	}
	
	return result;
}



/* override */ void FlicAnimation::SetCurrentFrame(unsigned frame)
{
	assert(frame < mFrames);

	if (mCurrentFrame == frame)
	{
		return;
	}

	unsigned from = 0;
	unsigned to = frame;

	if (frame > mCurrentFrame)
	{
		from = mCurrentFrame;
	}

	for (unsigned i = from; i <= to; ++i)
	{
		GetFrame(i);
	}

	mCurrentFrame = frame;
}



