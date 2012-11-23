local ModuleName = 'example'
local Example = {}



local ActionsOnExtension = 
{ 
	dat = "loadDAT",
	bmp = "loadBMP"
}



local Operations = {}



UTTModules[ModuleName] = Example


function Example.getModuleName()
	return 'Example'
end


function Example.getExtensions()
	return 'BMP files (*.bmp)|*.bmp|TXT files (*.txt)|*.txt'
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
	
	s = "bpp"..string.format(data2.BITCOUNT, "%d")
	local pal = Palette:new()
	
	local palBuffer = 0
	
	if (data2.BITCOUNT < 15) then
		local palsize = pal:GetPaletteSize(Palette[s], Palette.sfBMP)
		palBuffer = fh:read( palsize )
	end
	
	pal:Initiate( Palette[s], palBuffer, Palette.sfBMP, false )
	if pal:IsOk() then 
		local img = ImageInfo:new()
		
		if img:SetPalette( pal ) then
			local mask = IndexMask:new()
			local size =  data.FILESIZE - data.DATAOFFSET   --pal:GetCorrectImageSize(data2.WIDTH, data2.HEIGHT)
			local bytes = fh:read(size)
			
			if (data2.BITCOUNT < 8) then
				bytes, size = convertBufferToChar(bytes, size, data2.BITCOUNT)
			end
			
			-- -size inverts buffer to BMP style
			mask:SetMask( bytes, -(size), data2.WIDTH, data2.HEIGHT, -1, -1)
			
			if mask:IsOk() then
				img:SetImage( mask )
				editImage( img )
			end
		end
	end
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
BMPFileHeader[5] = { DATAOFFSET 	= "DWORD" 	}


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



print 'Example module loaded'
