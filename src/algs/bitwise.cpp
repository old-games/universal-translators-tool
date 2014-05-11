/***************************************************************
 * Name:      bitwise.cpp
 * Purpose:   implementation of bitwise functions 
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-11
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "bitwise.h"
#include "luacontrol.h"


// each function must have main body in C and Lua wrapper



// on entry: string, bit count
// for example, to unpack mono font command is: unpackBitBuffer( srcBuf, 1 )
int unpackBitBuffer(lua_State* L)
{
	int bitCount = 0;
	std::string s;
	if ( lua_gettop(L) != 2 || 
		!OOLUA::pull(L, bitCount) || 
		!OOLUA::pull(L, s))
	{
		wxLogError("unpackBitBuffer: function need a source buffer and source bit count");
		return 0;
	}

	unsigned int destSize = 0;
	char* res = UnpackBitBuffer( s.length(), s.c_str(), bitCount, destSize );

	lua_pushlstring (L, res, destSize);
	OOLUA::push(L, destSize);
	free(res);
	return 2;
}



char* UnpackBitBuffer( unsigned int size, const char* src, int bitCount, unsigned int& destSize )
{
	unsigned int dev = 8 / bitCount;
	destSize = size * dev;
	char* res = (char*) malloc( destSize );

	char bitMask = 1;
	for (int i = 1; i < bitCount; ++i)
	{
		bitMask <<= 1;
		bitMask |= 1;
	}

	unsigned char* dest = (unsigned char*) res;
	for (size_t i = 0; i < size; ++i)
	{
		dest += dev;
		for (size_t part = 0; part < dev; ++part)
		{
			--dest;
			const unsigned char shift = part * bitCount;
			*dest = (src[i] & (bitMask << shift) ) >> shift;
		}
		dest += dev;
	}

	return res;
}



//////////////////////////////////////////////////////////////////////////



namespace Lua
{
	void RegisterBitwiseFunctions()
	{
		LUA_REG_C_FUNCTION( unpackBitBuffer );
	}
}