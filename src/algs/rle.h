/***************************************************************
 * Name:      rle.h
 * Purpose:   declarations of known RLE algorithms
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-11
 * Copyright: Pavlovets Ilia 2012 
 * License:
 **************************************************************/

#ifndef RLEALGS_H_INCLUDED
#define RLEALGS_H_INCLUDED

namespace Lua
{
	void RegisterRLEFunctions();
}



char* UnpackLBMBody( const char* src, unsigned int destSize );
void UnpackFLIByteRun(wxByte* dest, const wxByte* src, unsigned width, unsigned height);
void UnpackFLCDelta(wxByte* dest, const wxByte* src, unsigned width);


#endif // RLEALGS_H_INCLUDED
