/***************************************************************
 * Name:      rle.cpp
 * Purpose:   implementation of known RLE algorithms
 * Author:    Pavlovets Ilia (ilia.pavlovets@gmail.com)
 * Created:   2012-12-11
 * Copyright: Pavlovets Ilia
 * License:
 **************************************************************/

#include "pch.h"
#include "rle.h"
#include "luacontrol.h"



int unpackLBMBody(lua_State* L)
{
	std::string s;
	unsigned int destSize = 0;

	if ( lua_gettop(L) != 2 || !OOLUA::pull2cpp(L, destSize) || !OOLUA::pull2cpp(L, s)  )
	{
		wxLogError("unpackLBMBody: function need a source buffer and destination buffer size");
		return 0;
	}

	char* res = UnpackLBMBody( s.c_str(), destSize );

	lua_pushlstring (L, res, destSize);
	OOLUA::push2lua(L, destSize);
	free(res);
	return 2;
}

char* UnpackLBMBody( const char* src, unsigned int destSize )
{
//   1.) Loop until we have Final length] byte's worth of data (Final length calculated from image size.)
//	 2.) If [Decompressed data length] < [Final length] then:
//   3. Read a byte [Value]
//   4. If the byte value > 128, then:
//      -> Read the next byte and output it (257 - value) times.
//         Move forward 2 bytes and return to 3.)
//      If the byte value < 128, then:
//      -> Read and output the next [value + 1] bytes
//         Move forward [Value + 2] bytes and return to 3.)
//      If the byte value = 128, then:
//      -> Exit loop (Stop decompressing)

	unsigned int currentSize = 0;
	char* destResult = (char*) malloc( destSize );
	char* dest = destResult;

	while (currentSize < destSize)
	{
		wxByte code = (wxByte) *src++;

		if (code == 0x80)
		{
			break;
		}

		size_t len = 0;

		if (code > 128)
		{
			char value = *src++;
			len = (0xFF - code) + 2;
			memset( dest, value, len );			
		}
		else
		{
			len = code + 1;
			memcpy(dest, src, len);
			src += len;
		}
		
		dest += len;
		currentSize += len;
	}

	return destResult;
}



//////////////////////////////////////////////////////////////////////////



namespace Lua
{
	void RegisterRLEFunctions()
	{
		LUA_REG_C_FUNCTION( unpackLBMBody );
	}
}