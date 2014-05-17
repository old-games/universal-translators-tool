#include "pch.h"
#include "flicchunks.h"
#include "palette.h"
#include "buffer.h"



//////////////////////////////////////////////////////////////////////////
/// FLIC Header



FlicHeader::FlicHeader(const FlicHeader& other):
	mSize			(other.mSize),
	mType			(other.mType),
	mFrames			(other.mFrames),
	mWidth			(other.mWidth),
	mHeight			(other.mHeight),
	mDepth			(other.mDepth),
	mFlags			(other.mFlags),
	mSpeed			(other.mSpeed),
	mReserved1		(other.mReserved1),
	mCreated		(other.mCreated),
	mCreator		(other.mCreator),
	mUpdated		(other.mUpdated),
	mUpdater		(other.mUpdater),
	mAspect_dx		(other.mAspect_dx),
	mAspect_dy		(other.mAspect_dy),
	mExt_flags		(other.mExt_flags),
	mKeyframes		(other.mKeyframes),
	mTotalframes	(other.mTotalframes),
	mReq_memory		(other.mReq_memory),
	mMax_regions	(other.mMax_regions),
	mTransp_num		(other.mTransp_num),
//	mReserved2		(other.mReserved2),
	mOframe1		(other.mOframe1),
	mOframe2		(other.mOframe2)
//	mReserved3		(other.mReserved3)
{
	memcpy(mReserved2, other.mReserved2, sizeof(mReserved2));
	memcpy(mReserved3, other.mReserved3, sizeof(mReserved3));
}



bool FlicHeader::Load(wxInputStream& input)
{
	bool success = IStateStore::LoadSimpleType(input, mSize) &&
		IStateStore::LoadSimpleType(input, mType) &&
		IStateStore::LoadSimpleType(input, mFrames) &&
		IStateStore::LoadSimpleType(input, mWidth) &&
		IStateStore::LoadSimpleType(input, mHeight) &&
		IStateStore::LoadSimpleType(input, mDepth) &&
		IStateStore::LoadSimpleType(input, mFlags) &&
		IStateStore::LoadSimpleType(input, mSpeed) &&
		IStateStore::LoadSimpleType(input, mReserved1) &&
		IStateStore::LoadSimpleType(input, mCreated) &&
		IStateStore::LoadSimpleType(input, mCreator) &&
		IStateStore::LoadSimpleType(input, mUpdated) &&
		IStateStore::LoadSimpleType(input, mUpdater) &&
		IStateStore::LoadSimpleType(input, mAspect_dx) &&
		IStateStore::LoadSimpleType(input, mAspect_dy) &&
		IStateStore::LoadSimpleType(input, mExt_flags) &&
		IStateStore::LoadSimpleType(input, mKeyframes) &&
		IStateStore::LoadSimpleType(input, mTotalframes) &&
		IStateStore::LoadSimpleType(input, mReq_memory) &&
		IStateStore::LoadSimpleType(input, mMax_regions) &&
		IStateStore::LoadSimpleType(input, mTransp_num) &&
		IStateStore::LoadData(input, mReserved2, sizeof(mReserved2)) &&
		IStateStore::LoadSimpleType(input, mOframe1) &&
		IStateStore::LoadSimpleType(input, mOframe2) &&
		IStateStore::LoadData(input, mReserved3, sizeof(mReserved3));
	return success;
}



bool FlicHeader::IsSupported() const
{
	FlicType t = (FlicType) mType;
	return t == FlicType::FLI || t == FlicType::FLIC ||
		t == FlicType::XCOMVID;
}



//////////////////////////////////////////////////////////////////////////
/// FlicChunck



FlicChunk::FlicChunk(wxUint16 chunkType, wxUint32 size):
	mSize(size),
	mType(chunkType),
	mEndIterator(mSubchunks.end())
{
}



FlicChunk::FlicChunk(const FlicChunk& other):
	mSizeIsFull(other.mSizeIsFull),
	mOffset(other.mOffset),
	mDataLoaded(false),
	mSubchunks(),
	mSize(other.mSize),
	mType(other.mType)
{
}


FlicChunk::~FlicChunk()
{
	free(mData);
}



///* virtual */ bool FlicChunk::LoadHeader(wxInputStream& input)
//{
//	bool success = IStateStore::LoadSimpleType(input, mSize) &&
//		IStateStore::LoadSimpleType(input, mType);
//	StoreOffset(input);
//// 	
//// 	wxFileOffset skip = mSize % 2 == 0 ? mSize : mSize + 1;
//// 	input.SeekI(skip + 10, wxFromCurrent);
//	return success;
//}



inline void FlicChunk::StoreOffset(wxInputStream& input)
{
	mOffset = input.SeekI(0, wxFromCurrent);
}



inline void FlicChunk::RestoreOffset(wxInputStream& input)
{
	input.SeekI(mOffset, wxFromStart);
}



BufferPtr FlicChunk::GetData() const
{
	return std::make_shared<Buffer>(mData, GetDataSize(), false);
}



/* virtual */ size_t FlicChunk::GetStructSize() const
{
	return sizeof(mSize) + sizeof(mType);
}



wxUint32 FlicChunk::GetDataSize() const
{
	return mSizeIsFull ? mSize - GetStructSize() : mSize;
}



/* virtual */ void FlicChunk::Skip(wxInputStream& stream)
{
	stream.SeekI(GetDataSize(), wxFromCurrent);
}



bool FlicChunk::LoadSubchunk(wxInputStream& stream, wxUint16 chunkType, wxUint32 size)
{
	FlicChunk::Ptr chunk;

	if (HasChunk(chunkType))
	{
		wxLogError("FlicChunk::LoadSubchunk error: already has %X chunk!", chunkType);
		return false;
	}

	switch (chunkType)
	{
		case PAL:
			chunk = std::make_shared<PaletteChunk>(chunkType, size);
		break;

		case PSTAMP:
			chunk = std::make_shared<StampChunk>(chunkType, size);
		break;

		case DELTA_FLC:
		case DELTA_FLI:
		case FLI_BRUN:
		case FLI_COPY:
			chunk = std::make_shared<ImageDataChunk>(chunkType, size);
		break;

		default:
			wxLogError("\tFlicChunk::LoadSubchunk error: unknown subchunk %X, size %d",
				chunkType, size);
	}

	if (chunk)
	{
		//chunk->PrintInfo();
		chunk->LoadHeader(stream);
		mSubchunks[chunkType] = chunk;
		mEndIterator = mSubchunks.end();
	}

	return chunk != nullptr;
}



bool FlicChunk::LoadSubchunks(wxInputStream& stream, size_t num)
{
	for (size_t i = 0; i < num; ++i)
	{
		wxUint32 size = 0;
		wxUint16 chunkType = 0;

		if (!IStateStore::LoadSimpleType(stream, size) ||
			!IStateStore::LoadSimpleType(stream, chunkType))
		{
			return false;
		}

		if (!LoadSubchunk(stream, chunkType, size))
		{
			return false;
		}
	}

	return true;
}



void FlicChunk::PrintInfo()
{
	wxLogMessage("Chunk %X, size %d", mType, mSize);
}



/* override */ bool FlicChunk::LoadData(wxInputStream& input)
{
	if (mDataLoaded)
	{
		return true;
	}
	
	RestoreOffset(input);
	size_t size = GetDataSize();
	mData = (wxByte*) malloc(size);

	if (!IStateStore::LoadData(input, mData, size))
	{
		free(mData);
		mData = nullptr;
		wxLogError("FlicChunk::LoadData error: last error code %d", input.GetLastError());
		return false;
	}

	mDataLoaded = true;
	return true;
}



//////////////////////////////////////////////////////////////////////////
/// DynamicFlicChunk



DynamicFlicChunk::DynamicFlicChunk(wxUint16 chunkType, wxUint32 size):
		FlicChunk(chunkType, size)
{
}



DynamicFlicChunk::DynamicFlicChunk(const DynamicFlicChunk& other):
	FlicChunk(other),
	DynamicChunk(other)
{
}



/* override */ bool DynamicFlicChunk::LoadHeader(wxInputStream& input)
{
	bool res = this->Load(input);

	if (res)
	{
		StoreOffset(input);
	}

	this->Skip(input);
	return res;
}



///* override */ bool DynamicFlicChunk::LoadData(wxInputStream& input)
//{
//	if (mDataLoaded)
//	{
//		return true;
//	}
//	
//	RestoreOffset(input);
//	size_t size = GetDataSize();
//	mData = (wxByte*) malloc(size);
//
//	if (!IStateStore::LoadData(input, mData, size))
//	{
//		free(mData);
//		mData = nullptr;
//		wxLogError("ImageDataChunk::LoadData error: last error code %d", input.GetLastError());
//		return false;
//	}
//
//	mDataLoaded = true;
//	return true;
//}




/* override */ size_t DynamicFlicChunk::GetStructSize() const
{
	return FlicChunk::GetStructSize() + this->GetDynamicStructSize();
}



///* override */ void DynamicFlicChunk::Skip(wxInputStream& stream)
//{
//	
//}



//////////////////////////////////////////////////////////////////////////
/// PrefixChunk


PrefixChunk::PrefixChunk(wxUint16 chunkType, wxUint32 size):
	FlicChunk(chunkType, size)
{}



/* override */ bool PrefixChunk::LoadHeader(wxInputStream& input)
{
	bool res = IStateStore::LoadSimpleType(input, mSubNum) &&
		IStateStore::LoadData(input, mReserved, sizeof(mReserved));

	if (res)
	{
		StoreOffset(input);
	}

	this->Skip(input);
	return res;
}


/* override */ size_t PrefixChunk::GetStructSize() const
{
	return FlicChunk::GetStructSize() + sizeof(mSubNum) + sizeof(mReserved);
}



//////////////////////////////////////////////////////////////////////////
/// StampChunk



StampChunk::StampChunk(wxUint16 chunkType, wxUint32 size):
	FlicChunk(chunkType, size)
{}



/* override */ bool StampChunk::LoadHeader(wxInputStream& input)
{
	bool res = IStateStore::LoadSimpleType(input, mWidth) &&
		IStateStore::LoadSimpleType(input, mHeight) &&
		IStateStore::LoadSimpleType(input, mXlate);

	if (res)
	{
		StoreOffset(input);
	}

	this->Skip(input);
	return res;
}



/* override */ size_t StampChunk::GetStructSize() const
{
	return FlicChunk::GetStructSize() + sizeof(mWidth) + sizeof(mHeight) + sizeof(mXlate);
}



//////////////////////////////////////////////////////////////////////////
/// FrameChunk



FrameChunk::FrameChunk(wxUint16 chunkType, wxUint32 size):
	FlicChunk(chunkType, size)
{}



/* override */ bool FrameChunk::LoadHeader(wxInputStream& input)
{
	bool res = IStateStore::LoadSimpleType(input, mSubNum) &&
		IStateStore::LoadSimpleType(input, mDelay) &&
		IStateStore::LoadSimpleType(input, mReserved) &&
		IStateStore::LoadSimpleType(input, mWidth) &&
		IStateStore::LoadSimpleType(input, mHeight);

	if (res)
	{
		StoreOffset(input);
	}

	LoadSubchunks(input, mSubNum);
	return res;
}



/* override */ size_t FrameChunk::GetStructSize() const
{
	return FlicChunk::GetStructSize() + sizeof(mSubNum) +
		sizeof(mDelay) + sizeof(mReserved) +
		sizeof(mWidth) + sizeof(mHeight);
}



/* override */ bool FrameChunk::LoadData(wxInputStream& stream)
{
	if (mDataLoaded)
	{
		return true;
	}

	RestoreOffset(stream);

	if (mSubNum == 0)
	{
		FlicChunk::Skip(stream);
		mDataLoaded = true;
		return true;
	}

	for (auto& subchunk: mSubchunks)
	{
		if (!subchunk.second->LoadData(stream))
		{
			return false;
		}
	}

	mDataLoaded = true;
	return true;
}



//////////////////////////////////////////////////////////////////////////
/// PaletteChunk



PaletteChunk::PaletteChunk(wxUint16 chunkType, wxUint32 size):
	FlicChunk(chunkType, size)
{
}



bool PaletteChunk::PalEntry::LoadPackets(wxInputStream& input, int colNum)
{
	bool res = IStateStore::LoadSimpleType(input, mSkip) &&
		IStateStore::LoadSimpleType(input, mNum);

	if (!res)
	{
		return false;
	}

	size_t size = mNum * 3;

	if (mNum == 0)
	{
		size = colNum * 3;
	}

	mData = (wxByte*) malloc(size);
	return IStateStore::LoadData(input, mData, size);
}



PaletteChunk::PalEntry::PalEntry(PalEntry&& tomove):
	mSkip(tomove.mSkip),
	mNum(tomove.mNum),
	mData(tomove.mData)
{
	tomove.mSkip = 0;
	tomove.mNum = 0;
	tomove.mData = nullptr;
}



UttColour PaletteChunk::PalEntry::GetColour(int n, int index) const
{
	wxByte* p = mData + (n * 3);
	return UttColour({p[0], p[1], p[2]}, index);
}



/* override */ bool PaletteChunk::LoadHeader(wxInputStream& input)
{
	bool res = IStateStore::LoadSimpleType(input, mPackets);

	if (res)
	{
		StoreOffset(input);
	}

	this->Skip(input);
	return res;
}



/* override */ size_t PaletteChunk::GetStructSize() const
{
	return FlicChunk::GetStructSize() + sizeof(mPackets);
}



/* override */ bool PaletteChunk::LoadData(wxInputStream& input)
{
	if (mDataLoaded)
	{
		return true;
	}

	RestoreOffset(input);
	
	for (wxUint16 i = 0; i < mPackets; ++i)
	{
		PalEntry entry;

		if (entry.LoadPackets(input, mColNum))
		{
			mPalEntries.emplace_back(std::move(entry));
		}
		else
		{
			return false;
		}
	}

	mDataLoaded = true;
	return true;
}



void PaletteChunk::ApplyToPalette(PalettePtr pal)
{
	unsigned index = 0;

	for (auto& entry: mPalEntries)
	{
		index += entry.mSkip;

		unsigned num = entry.mNum == 0 ? mColNum : entry.mNum;

		for (unsigned i = 0; i < num; ++i)
		{
			pal->SetColourByIndex(entry.GetColour(i, index++));
		}
	}
}



//////////////////////////////////////////////////////////////////////////
/// ImageDataChunk



ImageDataChunk::ImageDataChunk(wxUint16 chunkType, wxUint32 size):
	FlicChunk(chunkType, size)
{
}



/* override */ bool ImageDataChunk::LoadHeader(wxInputStream& input)
{
	StoreOffset(input);

	if (mType == FLI_COPY)
	{
		mSize += 2;
	}

	this->Skip(input);
	return true;
}



///* override */ bool ImageDataChunk::LoadData(wxInputStream& input)
//{
//	if (mDataLoaded)
//	{
//		return true;
//	}
//	
//	RestoreOffset(input);
//	size_t size = GetDataSize();
//	mData = (wxByte*) malloc(size);
//
//	if (!IStateStore::LoadData(input, mData, size))
//	{
//		free(mData);
//		mData = nullptr;
//		wxLogError("ImageDataChunk::LoadData error: last error code %d", input.GetLastError());
//		return false;
//	}
//
//	mDataLoaded = true;
//	return true;
//}
