/***************************************************************
 * Name:      flic.h
 * Purpose:   FLIC support
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-12
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/


#ifndef __FLIC_H__
#define __FLIC_H__

#include "animation.h"
#include "flicchunks.h"
#include "dynamicchunk.h"



//////////////////////////////////////////////////////////////////////////
/// FlicAnimation



class FlicAnimation: public Animation
{

typedef std::map<wxUint16, DynamicFlicChunk::Ptr> DynamicChunkMap;
typedef std::map<wxUint16, FlicChunk::ChunkList> ChunkMap;

public:

	FlicAnimation();

	bool IsOk() const { return mInputStream != nullptr; }
	bool OpenFlicFile(const std::string& filename);
	bool Open(wxInputStream& stream);
	void AddDynamicChunk(wxUint16 type, DynamicFlicChunk::Ptr chunk);

	size_t GetChunksCount(wxUint16 type) const;
	FlicChunk::Ptr GetChunk(wxUint16 type, size_t n) const;
	DynamicFlicChunk::Ptr GetDynamicChunk(wxUint16 type, size_t n) const;

	virtual ImageInfoPtr GetFrame(unsigned frame) override;
	virtual void SetCurrentFrame(unsigned frame) override;

private:

	bool LoadChunk(wxInputStream& stream, wxUint16 chunkType, wxUint32 size);
	FlicChunk::Ptr CreateDynamicChunk(wxUint16 chunkType, wxUint32 size);
	ImageDataChunk::Ptr CheckImageChunk(FrameChunk::Ptr chunk) const;

	wxString			mFilename;
	FlicHeader			mHeader;
	DynamicChunkMap		mDynamicChunks;
	ChunkMap			mLoadedChunks;
	InputStreamPtr		mInputStream;
	PalettePtr			mPalette;
};



#endif // __FLIC_H__
