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

	if ( lua_gettop(L) != 2 || !OOLUA::pull(L, destSize)
		|| !OOLUA::pull(L, s)  )
	{
		wxLogError("unpackLBMBody: function need a source buffer and destination buffer size");
		return 0;
	}

	char* res = UnpackLBMBody( s.c_str(), destSize );

	lua_pushlstring (L, res, destSize);
	OOLUA::push(L, destSize);
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



#ifndef X64
void UnpackFLIByteRun(wxByte* dest, const wxByte* src, unsigned width, unsigned height)
{
	assert(src);

	__asm
	{
		mov esi, src
		mov edi, dest
		xor eax, eax
		xor ecx, ecx
		mov ecx, height

main_loop:
		push ecx
		xor edx, edx
		lodsb	// ignoring packets number, it is for old FLI format
line_loop:		// unpack line
		xor ecx, ecx
		lodsb
		mov cl, al
		
		test al, 0x80
		jz more_zero
			neg cl
			add edx, ecx
			rep movsb
			jmp line_loop_end
more_zero:
			add edx, ecx
			lodsb
			rep stosb
line_loop_end:
		cmp edx, width
		jb line_loop

		pop ecx
		dec ecx
		jnz main_loop

	}
}
#else
void UnpackFLIByteRun(wxByte* dest, const wxByte* src, unsigned width, unsigned height)
{
	assert(src);

	for (unsigned y = 0; y < height; ++y)
	{
		unsigned char packets = (unsigned char) (*src++); // ignoring
		++packets;

		unsigned x = 0;

		while (x < width)
		{
			wxByte code = *src++;
			size_t len = code;

			if (code < 0x80)
			{
				wxByte value = *src++;
				memset( dest, value, code );
			}
			else
			{
				len = code + (-0x80);
				memcpy(dest, src, len);
				src += len;
			}

			dest += len;
			x += len;
		}
	}
}
#endif



#ifndef X64
void UnpackFLCDelta(wxByte* dest, const wxByte* src, unsigned width)
{
	assert(dest && src);
	__asm
	{
		mov esi, src
		mov edi, dest
		xor ecx, ecx
		xor eax, eax
		lodsw
		mov cx, ax
main_loop:
		lodsw
opcode_loop:
		test ax, 0x8000	// if highest bit is 1 - this is opcode wich contain number of lines to skip
		jz unpack		// else - number of packets in line
			test ax, 0x4000 // if 14 bit is 1 - this is holder of last byte for odd width frame
							// after this bit always goes number of packets
			jz last
			// skip lines
				neg ax
				mul width
				add edi, eax
				lodsw
				jmp opcode_loop
			last:
				mov bl, al // store last line byte
				lodsw
				jmp opcode_loop
unpack:
		//
		push edi
		push ecx
		xor ecx, ecx
		mov cx, ax
		// unpack cx packets
		unpack_loop:
			xor eax, eax
			lodsb
			add edi, eax
			lodsb
			mov edx, ecx
			// unpack packet data
			test al, 0x80
			jz more_zero
				mov cl, al
				neg cl
				lodsw
				rep stosw
				jmp unpack_loop_end
		more_zero:
				mov cl, al
				shl cx, 1
				rep movsb
		unpack_loop_end:
			mov ecx, edx
			dec cx
			jnz unpack_loop
		pop ecx
		pop edi
		add edi, width
			test width, 1	// if odd frame width using
			jz not_odd
				dec edi
				mov al, bl
				stosb
			not_odd:
		dec cx
		jnz main_loop
	}
}
#else
void UnpackFLCDelta(wxByte* dest, const wxByte* src, unsigned width)
{
	assert(dest && src);
	wxUint16 lines = *((wxUint16*) src);
	++src; ++src;
	bool odd = width % 2 != 0;

	for (unsigned y = 0; y < lines; ++y)
	{
		wxInt16 opcode = *((wxInt16*) src);
		++src; ++src;
		wxByte lastByte = 0;
		unsigned skipLines = 0;
		bool hasLastByte = false;

		while ((opcode & 0x8000) != 0)
		{
			if ((opcode & 0x4000) != 0)
			{
				skipLines += -opcode;
			}
			else
			{
				hasLastByte = true;
				lastByte = (wxByte) (opcode & 0x00FF);
			}

			opcode = *((wxInt16*) src);
			++src; ++src;
		}

		dest += skipLines * width;
		wxByte* oldDest = dest;

		for (int i = 0; i < opcode; ++i)
		{
			wxByte skip = *src++;
			dest += skip;
			char code = *src++;

			if (code <= 0)
			{
				size_t len = -code;
				wxByte one = *src++;
				wxByte two = *src++;

				for (size_t i = 0; i < len; ++i)
				{
					*dest++ = one;
					*dest++ = two;
				}
			}
			else
			{
				size_t len = code;
				len <<= 1;
				memcpy(dest, src, len);
				src += len;
				dest += len;
			}
		}

		dest = oldDest + width;

		if (odd && hasLastByte)
		{
			--dest;
			*dest++ = lastByte;
		}
	}
}
#endif



//////////////////////////////////////////////////////////////////////////



namespace Lua
{
	void RegisterRLEFunctions()
	{
		LUA_REG_C_FUNCTION( unpackLBMBody );
	}
}