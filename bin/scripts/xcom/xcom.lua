local PalName = 'PALETTES.DAT'
local PalSize = 768

xcomFontInfo = 
{
	-- UFO1DOS
	{
		execInfo = 
		{
			name = "ufo2exe/tactical.exe"
		},
		
		biglets =	
		{ 
			width = 16, height = 16, palette = 1
		}, 
		
		smallset = 
		{ 
			width = 8, height = 9, palette = 1
		} 
	},
	
	-- UFO2WIN
	{
		execInfo = 
		{
			name = "Terror From the Deep.exe"
		},
		
		biglets = 
		{ 
			width = 16, height = 16, 
			baseLine = 13, smallLine = 4,
			palette = 0, 
			offset = 567576, num = 141		--width info
		}, 
		
		smallset = 
		{ 
			width = 8, height = 9, 
			baseLine = 8, smallLine = 2,
			palette = 0, 
			offset = 567412, num = 160
		} 
	}
}



function GetXComPalette( path, n )
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



function GetFontWidth(fileName, offset, num, isBiglets)
	local fh = assert(io.open(fileName, "rb"))
	
	if not fh then
		return
	end
	local bytes = ''
	fh:seek("set", offset)
	if isBiglets ~= true then
		bytes = fh:read( num )
		fh:close()
	else
		local tmp
		for i = 1, num do
			tmp = fh:read(8)
			bytes = bytes..getStrChar(tmp, 4)
		end
	end
	return bytes
end





