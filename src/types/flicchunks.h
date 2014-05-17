/***************************************************************
 * Name:      flicchunks.h
 * Purpose:   FLIC chunks
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2014-05-13
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/


#ifndef __FLIC_CHUNKS_H__
#define __FLIC_CHUNKS_H__



#include "dynamicchunk.h"

//typedef struct {
//  DWORD size;          /* Size of FLIC including this header */
//  WORD  type;          /* File type 0xAF11, 0xAF12, 0xAF30, 0xAF44, ... */
//  WORD  frames;        /* Number of frames in first segment */
//  WORD  width;         /* FLIC width in pixels */
//  WORD  height;        /* FLIC height in pixels */
//  WORD  depth;         /* Bits per pixel (usually 8) */
//  WORD  flags;         /* Set to zero or to three */
//  DWORD speed;         /* Delay between frames */
//  WORD  reserved1;     /* Set to zero */
//  DWORD created;       /* Date of FLIC creation (FLC only) */
//  DWORD creator;       /* Serial number or compiler id (FLC only) */
//  DWORD updated;       /* Date of FLIC update (FLC only) */
//  DWORD updater;       /* Serial number (FLC only), see creator */
//  WORD  aspect_dx;     /* Width of square rectangle (FLC only) */
//  WORD  aspect_dy;     /* Height of square rectangle (FLC only) */
//  WORD  ext_flags;     /* EGI: flags for specific EGI extensions */
//  WORD  keyframes;     /* EGI: key-image frequency */
//  WORD  totalframes;   /* EGI: total number of frames (segments) */
//  DWORD req_memory;    /* EGI: maximum chunk size (uncompressed) */
//  WORD  max_regions;   /* EGI: max. number of regions in a CHK_REGION chunk */
//  WORD  transp_num;    /* EGI: number of transparent levels */
//  BYTE  reserved2[24]; /* Set to zero */
//  DWORD oframe1;       /* Offset to frame 1 (FLC only) */
//  DWORD oframe2;       /* Offset to frame 2 (FLC only) */
//  BYTE  reserved3[40]; /* Set to zero */
//} FLIC_HEADER;



enum class FlicType
{
	FLI = 0xAF11,			// For FLI files
	FLIC = 0xAF12,			// For standard FLC files (with an 8-bit colour depth). FLX files (both "Tempra FLX" and "Autodesk FLX") also use this header type.
	XCOMVID = 0xAF48,
	FHUFFMAN = 0xAF30,		// For FLIC files that use Huffman or BWT compression. These FLIC files can also have a colour resolution that is different from 8 bits per pixel.
	FRSHIFT = 0xAF31,		// For FLIC files that use "frame shift" compression. These FLIC files may use additional compression schemes like Huffman and BWT; They can also have a colour resolution that is different from 8 bits per pixel.
	FNOT8BPP = 0xAF44		// For FLIC files with a colour depth other than 8. The DTA program (by Dave K. Mason) makes FLIC files with a colour depth of 1, 15, 16 or 24 bits per pixel. EGI version 3.0 (and later) supports 16-bpp FLIC files.
};



enum KnownChunks: wxUint16
{
// sub chunks
	CEL = 3,		// CEL_DATA             registration and transparency
	PAL = 4,		// COLOR_256            256-level colour palette
	DELTA_FLC = 7,	// DELTA_FLC (FLI_SS2)  delta image, word oriented RLE
	PAL64 = 11,		// COLOR_64             64-level colour palette
	DELTA_FLI = 12,	// DELTA_FLI (FLI_LC)   delta image, byte oriented RLE
	BLACK = 13,		// BLACK                full black frame (rare)
	FLI_BRUN = 15,	// BYTE_RUN (FLI_BRUN)  full image, byte oriented RLE
	FLI_COPY = 16,	// FLI_COPY             uncompressed image (rare)
	PSTAMP = 18,	// PSTAMP               postage stamp (icon of the first frame)
	DTA_BRUN = 25,	// DTA_BRUN             full image, pixel oriented RLE
	DTA_COPY = 26,	// DTA_COPY             uncompressed image
	DTA_LC = 27,	// DTA_LC               delta image, pixel oriented RLE
	LABEL = 31,		// LABEL                frame label
	MASK = 32,		// BMP_MASK             bitmap mask

// main chunks
	PREFIX = 0xF100,
	SCRIPT = 0xF1E0,
	FRAME = 0xF1FA,
	SEGMENT = 0xF1FB,
	HUFFMAN = 0xF1FC
};




class FlicHeader final
{
public:
	
	FlicHeader() = default;
	FlicHeader(const FlicHeader& other);

	bool Load(wxInputStream& input);
	bool IsSupported() const;

	inline wxUint16 GetType() const { return mType; }
	inline unsigned GetWidth() const { return mWidth; }
	inline unsigned GetHeight() const { return mHeight; }
	inline unsigned GetSpeed() const { return mSpeed; }

private:

	wxUint32	mSize = 0;          /* Size of FLIC including this header */
	wxUint16	mType = 0;          /* File type 0xAF11, 0xAF12, 0xAF30, 0xAF44, ... */
	wxUint16	mFrames = 0;        /* Number of frames in first segment */
	wxUint16	mWidth = 0;         /* FLIC width in pixels */
	wxUint16	mHeight = 0;        /* FLIC height in pixels */
	wxUint16	mDepth = 0;         /* Bits per pixel (usually 8) */
	wxUint16	mFlags = 0;         /* Set to zero or to three */
	wxUint32	mSpeed = 0;         /* Delay between frames */
	wxUint16	mReserved1 = 0;     /* Set to zero */
	wxUint32	mCreated = 0;       /* Date of FLIC creation (FLC only) */
	wxUint32	mCreator = 0;       /* Serial number or compiler id (FLC only) */
	wxUint32	mUpdated = 0;       /* Date of FLIC update (FLC only) */
	wxUint32	mUpdater = 0;       /* Serial number (FLC only), see creator */
	wxUint16	mAspect_dx = 0;     /* Width of square rectangle (FLC only) */
	wxUint16	mAspect_dy = 0;     /* Height of square rectangle (FLC only) */
	wxUint16	mExt_flags = 0;     /* EGI: flags for specific EGI extensions */
	wxUint16	mKeyframes = 0;     /* EGI: key-image frequency */
	wxUint16	mTotalframes = 0;   /* EGI: total number of frames (segments) */
	wxUint32	mReq_memory = 0;    /* EGI: maximum chunk size (uncompressed) */
	wxUint16	mMax_regions = 0;   /* EGI: max. number of regions in a CHK_REGION chunk */
	wxUint16	mTransp_num = 0;    /* EGI: number of transparent levels */
	wxUint8		mReserved2[24];     /* Set to zero */
	wxUint32	mOframe1 = 0;       /* Offset to frame 1 (FLC only) */
	wxUint32	mOframe2 = 0;       /* Offset to frame 2 (FLC only) */
	wxUint8		mReserved3[40];     /* Set to zero */
};



//////////////////////////////////////////////////////////////////////////
/// FlicChunk



class FlicChunk
{
public:
	typedef std::shared_ptr<FlicChunk> Ptr;
	typedef std::list<Ptr> ChunkList;


	FlicChunk() = delete;
	FlicChunk(wxUint16 chunkType, wxUint32 size);
	FlicChunk(const FlicChunk& other);

	virtual ~FlicChunk();

	virtual bool LoadHeader(wxInputStream& input) = 0;
	virtual bool LoadData(wxInputStream& );
	
	inline wxUint32 GetSize() const { return mSize; }
	wxUint32 GetDataSize() const;
	//virtual void* GetData() const { return mData; }
	//inline const wxByte* GetData() const { return mData; }
	BufferPtr GetData() const;

	inline wxUint16 GetType() const { return mType; }

	virtual size_t GetStructSize() const;
	virtual void Skip(wxInputStream& stream);

	void PrintInfo();

	void SetSizeFull(bool b) { mSizeIsFull = b; }

	inline bool HasChunk(wxUint16 chunkType) const
		{ return mSubchunks.find(chunkType) != mEndIterator; }
	
	template<typename T>
	inline std::shared_ptr<T> GetSubchunk(wxUint16 chunkType)
	{
		assert(HasChunk(chunkType));
		return std::static_pointer_cast<T>(mSubchunks.find(chunkType)->second);
	}

protected:

	typedef std::map<wxUint16, Ptr> SubchunkMap;

	bool LoadSubchunk(wxInputStream& stream, wxUint16 chunkType, wxUint32 size);
	bool LoadSubchunks(wxInputStream& stream, size_t num);
	void StoreOffset(wxInputStream& input);
	void RestoreOffset(wxInputStream& input);

	bool			mSizeIsFull = true; // if true then mSize is full with header else only data
	wxFileOffset	mOffset = wxInvalidOffset;
	bool			mDataLoaded = false;
	SubchunkMap		mSubchunks;
	SubchunkMap::const_iterator	mEndIterator;
	wxUint32		mSize = 0;
	wxUint16		mType = 0;
	wxByte*			mData = nullptr;
};



//////////////////////////////////////////////////////////////////////////
/// DynamicFlicChunk


class DynamicFlicChunk: public FlicChunk, public DynamicChunk
{
public:

	typedef std::shared_ptr<DynamicFlicChunk> Ptr;

	DynamicFlicChunk(): FlicChunk(0, 0) {};
	explicit DynamicFlicChunk(wxUint16 chunkType, wxUint32 size);
	DynamicFlicChunk(const DynamicFlicChunk& other);

	Ptr Clone() const { return std::make_shared<DynamicFlicChunk>(*this); }
	
	Ptr Clone(wxUint16 chunkType, wxUint32 size)
	{
		Ptr res = std::make_shared<DynamicFlicChunk>(*this);
		res->mSize = size;
		res->mType = chunkType;
		return res;
	}

	virtual bool LoadHeader(wxInputStream& input) override;
	virtual size_t GetStructSize() const override;
	//virtual void Skip(wxInputStream& stream) override;

private:

};


//typedef struct {
//  DWORD size;           /* Size of the chunk, including subchunks */
//  WORD  type;           /* Chunk type: 0xF100 */
//  WORD  chunks;         /* Number of subchunks */
//  BYTE  reserved[8];    /* Reserved, set to 0 */
//} PREFIX_HDR;


class PrefixChunk: public FlicChunk
{
public:

	PrefixChunk() = delete;
	explicit PrefixChunk(wxUint16 chunkType, wxUint32 size);

	virtual bool LoadHeader(wxInputStream& input) override;
	virtual size_t GetStructSize() const override;

private:

	wxUint16	mSubNum = 0;
	wxUint8		mReserved[8];
};


// typedef struct {
//   DWORD size;           /* Size of this chunk */
//   WORD  type;           /* Chunk type: 18 */
//   WORD  height;         /* Height of the postage stamp */
//   WORD  width;          /* Width of the postage stamp */
//   WORD  xlate;          /* Colour translation, always 1 */
// } PSTAMP;


class StampChunk: public FlicChunk
{
public:

	StampChunk() = delete;
	explicit StampChunk(wxUint16 chunkType, wxUint32 size);

	virtual bool LoadHeader(wxInputStream& input) override;
	virtual size_t GetStructSize() const override;

private:

	wxUint16	mWidth = 0;
	wxUint16	mHeight = 0;
	wxUint16	mXlate = 0;
};



// typedef struct {
//   DWORD size;          /* Size of the chunk, including subchunks */
//   WORD  type;          /* Chunk type: 0xF1FA */
//   WORD  chunks;        /* Number of subchunks */
//   WORD  delay;         /* Delay in milliseconds */
//   short reserved;      /* Always zero */
//   ushort width;        /* Frame width override (if non-zero) */
//   ushort height;       /* Frame height override (if non-zero) */
// } FRAME_TYPE;


class FrameChunk: public FlicChunk
{
public:
	typedef std::shared_ptr<FrameChunk> Ptr;

	FrameChunk() = delete;
	explicit FrameChunk(wxUint16 chunkType, wxUint32 size);

	virtual bool LoadHeader(wxInputStream& input) override;
	virtual size_t GetStructSize() const override;
	virtual bool LoadData(wxInputStream& stream) override;

	inline wxUint16 GetWidth() const { return mWidth; }
	inline wxUint16 GetHeight() const { return mHeight; }
	inline wxUint16 GetDelay() const { return mDelay; }

private:

	wxUint16	mSubNum = 0;
	wxUint16	mDelay = 0;
	wxUint16	mReserved = 0;
	wxUint16	mWidth = 0;
	wxUint16	mHeight = 0;
};



//////////////////////////////////////////////////////////////////////////
/// PaletteChunk



class PaletteChunk: public FlicChunk
{
public:

	PaletteChunk() = delete;
	explicit PaletteChunk(wxUint16 chunkType, wxUint32 size);

	virtual bool LoadHeader(wxInputStream& input) override;
	virtual size_t GetStructSize() const override;
	virtual bool LoadData(wxInputStream& input) override;
	void ApplyToPalette(PalettePtr pal);

private:

	struct PalEntry final
	{
		PalEntry() = default;
		PalEntry(const PalEntry&) = delete;
		PalEntry(PalEntry&& tomove);
		~PalEntry() { free(mData); }

		bool LoadPackets(wxInputStream& input, int colNum);
		UttColour GetColour(int n, int index) const;

		wxUint8		mSkip = 0;
		wxUint8		mNum = 0;
		wxByte*		mData = nullptr;
	};

	wxUint16				mPackets = 0;
	std::list<PalEntry>		mPalEntries;
	int						mColNum = 256; // TODO: add support for 64-level palette
};



//////////////////////////////////////////////////////////////////////////
/// ImageDataChunk



class ImageDataChunk: public FlicChunk
{
public:
	typedef std::shared_ptr<ImageDataChunk> Ptr;

	ImageDataChunk() = delete;
	explicit ImageDataChunk(wxUint16 chunkType, wxUint32 size);

	~ImageDataChunk() = default;

	virtual bool LoadHeader(wxInputStream& input) override;
	//virtual bool LoadData(wxInputStream& input) override;

	inline const wxByte* GetData() const { return mData; }

};




#endif // __FLIC_CHUNKS_H__

