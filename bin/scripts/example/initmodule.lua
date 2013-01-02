local ModuleName = 'example'
local Example = {}


UTTModules[ModuleName] = Example


function Example.getModuleName()
	return 'Example'
end




function loadBMP( filename )
	local fh = assert(io.open(filename, "rb"))
	
	if not fh then
		return
	end
	
	local data = readData( fh, BMPFileHeader )
	showTable( data )
	
	if(data.ID ~= 0x4D42) then
		print("Not a bitmap file (Invalid BMP id) ", data.ID);
		return;
	end
	
	local data2 = readData(fh, BMPInfoHeader )
	showTable( data2 )
	
	local s = "bpp"..string.format(data2.BITCOUNT, "%d")
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
			local size =  data2.SIZEIMAGE    --pal:GetCorrectImageSize(data2.WIDTH, data2.HEIGHT)
			
			if size == 0 then
				size = data.FILESIZE - data.DATAOFFSET
			end
			
			local bytes = fh:read(size)
			
			if (data2.BITCOUNT < 8) then
				bytes, size = convertBufferToChar(bytes, size, data2.BITCOUNT)
			end
			
			-- -size inverts buffer to BMP style
			mask:SetMask( bytes, -(size), data2.WIDTH, data2.HEIGHT, -1, -1)
			
			if mask:IsOk() then
				img:SetImage( mask )
			end
		end
	end
	fh:close()
	
	return img
end



function loadTXT( filename )
	local fh = assert(io.open(filename, "r"))
	if not fh then
		return
	end
	for line in fh:lines() do print(line) end
	fh:close()
end



function Example.ImportImage()
	local fileName = openFileDialog("BMP files (*.bmp)|*.bmp")
	
	if fileName ~= nil then
		local image = loadBMP( fileName )
		
		if image then
			editImage(image)
		end
	end
end


print 'Example module loaded'
