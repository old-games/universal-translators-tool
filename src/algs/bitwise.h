/***************************************************************
 * Name:      bitwise.h
 * Purpose:   declaration of bitwise functions
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-11
 * Copyright: Pavlovets Ilia 2012 
 * License:
 **************************************************************/

#ifndef BITWISEALGS_H_INCLUDED
#define BITWISEALGS_H_INCLUDED



namespace Lua
{
	void RegisterBitwiseFunctions();
}



char* UnpackBitBuffer( unsigned int size, const char* src, int bitCount, unsigned int& destSize );


#endif // BITWISEALGS_H_INCLUDED
