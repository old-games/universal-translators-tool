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



class FlicHeader final
{
public:
	
	FlicHeader() = default;
	FlicHeader(const FlicHeader& other);

	bool Load(wxInputStream& input);

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



#endif // __FLIC_H__
