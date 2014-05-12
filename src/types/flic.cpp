#include "pch.h"
#include "flic.h"



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



