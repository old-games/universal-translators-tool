local PalName = 'geodata/PALETTES.DAT'
local PalSize = 768
currentVersion = 2

KnownImageNames = { "lang", "back", "geobord", "up_bord2"}

imageParams = 
{
	lang = 
	{
		width = 64,
		height = 200,
		palette = 0
	},
	
	back = 
	{
		width = 320,
		height = 200,
		palette = 0
	},
	
	geobord = 
	{
		width = 320,
		height = 200,
		palette = 0
	},
	
	up_bord2 = 
	{
		width = 320,
		height = 200,
		palette = 2
	} 
}

local xcomFontInfo = 
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



local function GetXComPalette( path, n )
	local fh = assert(io.open(path..PalName, "rb"))
	
	if not fh then
		return
	end
	
	local fileSize = fh:seek("end")
	local maxPal = fileSize / (PalSize + 6)
	if n >= maxPal then
		print (PalName.." contains only ", maxPal, " palettes")
		return
	end
	
	n = n * (PalSize + 6)
	fh:seek("set", n)
	local bytes = fh:read( PalSize )
	fh:close()
	return bytes
end



function CreateXcomPalette( path, n, owner )
	local palBuffer = GetXComPalette(path, n)
	if palBuffer ~= nil then
		local pal = Palette:new()
		if pal:Initiate( Palette.bpp8, palBuffer, Palette.sfPlain, true ) then
			if owner:SetPalette( pal ) then
				print "Palette successfully loaded."
				return true
			end
		end
	end
	print "Palette not loaded!"
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



function LoadXcomFont( path, name, fh )
	local exec = xcomFontInfo[currentVersion].execInfo
	local params = xcomFontInfo[currentVersion][name]
	local width = params.width
	local height = params.height
	local bufsize = width * height
	local num = 0
	local font = FontInfo:new()
	
	local symWidths = GetFontWidth(path.."../"..exec.name, 
		params.offset, params.num, name == 'biglets')
	
	font:SetValues( width, height, 3, 3, 0, params.baseLine, 0, params.smallLine )
	
	if not CreateXcomPalette( path.."../", params.palette, font ) then
		return false
	end
	
	print "Font loading..."
	
	repeat
	
		local bytes = fh:read( bufsize )
		if bytes ~= nil and bytes:len() == bufsize then
		
			num = num + 1
			
			local w = width
			
			-- in xcom games the quantity of symbols is more than 
			-- width array in EXE files 
			if symWidths ~= nil and num <= #symWidths then
				w = getStrInt(symWidths, num)
			end
			
			local mask = IndexMask:new()
			mask:SetMask( bytes, bufsize, width, height, width, height)
			
			if mask:IsOk() then
				font:AddSymbolIndexed( mask, w, height )
			end
		end
		
	until not bytes
	
	print ("Symbols loaded: ", num)
	editFont( font )
end



function LoadXcomImage( path, name, key, fh )
	local params = imageParams[key]
	local width = params.width
	local height = params.height
	local bufsize = width * height
	local image = ImageInfo:new()
	
	if not 	CreateXcomPalette( path.."../", params.palette, image ) then
		return
	end
	
	print "Image loading..."
	
	local bytes = fh:read( bufsize )
	if bytes ~= nil and bytes:len() == bufsize then
		local mask = IndexMask:new()
		mask:SetMask( bytes, bufsize, width, height, width, height)
		if mask:IsOk() then
			image:SetImage( mask )
			editImage( image )
		end
	end
end

