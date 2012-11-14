local ModuleName = 'example'
local Example = {}



local ActionsOnExtension = 
{ 
	dat = "loadDAT",
	bmp = "loadBMP",
	txt = "loadTXT"
}



local Operations = {}



UTTModules[ModuleName] = Example



function Example.getExtensions()
	return 'BIGLETS.DAT (biglets.dat)|biglets.dat|SMALLSET.DAT (smallset.dat)|smallset.dat|BMP files (*.bmp)|*.bmp|TXT files (*.txt)|*.txt'
end



function Example.openFile( fileName )
	local fileName = string.lower( fileName )
	local vol, path, name, ext = parseFileName( fileName )
	local key = ActionsOnExtension[ ext ]
	if key == nil then
		print( "Can't find function for '"..ext.."' extension" )
		return
	end
	Operations[ key ]( fileName )
end



function Operations.loadBMP( filename )
	local fh = assert(io.open(filename, "rb"))
	if not fh then
		return
	end
	data = readData( fh, BMPFileHeader )
	showTable( data )
	if(data.ID ~= 0x4D42) then
		print("Not a bitmap file (Invalid BMP id) ", data.ID);
		return;
	end
	data2 = readData(fh, BMPInfoHeader )
	showTable( data2 )
	fh:close()
end



function Operations.loadTXT( filename )
	local fh = assert(io.open(filename, "r"))
	if not fh then
		return
	end
	for line in fh:lines() do logWrite(line) end
	fh:close()
end


BMPFileHeader = {}
BMPFileHeader[1] = { ID 			= "WORD" 	}
BMPFileHeader[2] = { FILESIZE 		= "LONG" 	}
BMPFileHeader[3] = { RESERVED1 		= "WORD" 	}
BMPFileHeader[4] = { RESERVED2 		= "WORD" 	}
BMPFileHeader[5] = { DATA_OFFSET 	= "DWORD" 	}


BMPInfoHeader = {}
BMPInfoHeader[1] 	= { DATASIZE		= "DWORD" 	}
BMPInfoHeader[2] 	= { WIDTH			= "LONG" 	}
BMPInfoHeader[3] 	= { HEIGHT			= "LONG" 	}
BMPInfoHeader[4] 	= { PLANES			= "WORD" 	}
BMPInfoHeader[5] 	= { BITCOUNT		= "WORD" 	}
BMPInfoHeader[6] 	= { COMPRESSION 	= "DWORD" 	}
BMPInfoHeader[7] 	= { SIZEIMAGE		= "DWORD" 	}
BMPInfoHeader[8] 	= { XPELSPERMETER	= "LONG" 	}
BMPInfoHeader[9] 	= { YPELSPERMETER	= "LONG" 	}
BMPInfoHeader[10] 	= { CLRUSED			= "DWORD" 	}
BMPInfoHeader[11] 	= { CLRIMPORTANT	= "DWORD" 	}



--[[


X-COM / UFO section


--]]



local PalName = 'PALETTES.DAT'
local PalSize = 768



local function GetXComPalette( path, n )
	local fh = assert(io.open(path..PalName, "rb"))
	
	if not fh then
		return
	end
	
	local maxPal = fh:seek("end") / PalSize
	
	if n >= maxPal then
		print (PalName.." contains only ", maxPal, " palettes")
		return
	end
	
	fh:seek("set", n * PalSize)
	local bytes = fh:read( PalSize )
	fh:close()
	return bytes
end



function Operations.loadDAT( filename )
	local vol, path, name, ext = parseFileName( filename )

	local fh = assert(io.open(filename, "rb"))
	if not fh then
		return
	end
	
	local params = { biglets = {16, 16}, smallset = {8, 8} }
	local width = params[name][1]
	local height = params[name][2]
	local bufsize = width * height
	local num = 0
	local font = FontInfo:new()
	
	--void FontInfo::SetValues( int maxHeight, int minHeight, int maxWidth, int minWidth,
	--			int bpp /* BPP::bppMono */,
	--			int fontCodePage /* wxFONTENCODING_DEFAULT */,
	--			int baseLine /* 0 */,
	--			int capLine /* 0 */,
	--			int lowLine /* 0 */)
	
	font:SetValues( width,  height, 0, 0, BPP.bpp8, 0, 0, 0, 0 )
	
	local pal = GetXComPalette(vol..path..'/', 0)
	if pal ~= nil then
		font:SetPalette( pal, true )
		setPalette( BPP.bpp8, pal, true )
	end
	
	print "Font loading"
	
	repeat
		local bytes = fh:read( bufsize )
		num = num + 1
		if bytes ~= nil and bytes:len() == bufsize then
			font:AddSymbol( bytes, 16, 16 )
		end
	until not bytes
	
	print ("Symbols: ", num)
	fh:close()
	editFont( font )
end






print 'Example module loaded'
