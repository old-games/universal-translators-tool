local PalName = 'geodata/PALETTES.DAT'
local PalSize = 768


currentVersion = 1

local KnownImageNames = 
{
	-- UFO1DOS 
	{ "lang", "back", "geobord", "up_bord2"},
	--	XCOM2WIN 
	{ "lang", "back", "geobord", "up_bord2"} 
}

local imageParams = 
{
	-- UFO1DOS
	{
		lang = 
		{
			width = 64,
			height = 154,
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
	},
	
	-- XCOM2WIN
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
			width = 16, height = 16, 
			baseLine = 13, smallLine = 4,
			palette = 4, 
			offset = 388903, num = 129
		}, 
		
		smallset = 
		{ 
			width = 8, height = 9, 
			baseLine = 8, smallLine = 2,
			palette = 4, 
			offset = 388774, num = 129
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



local function GetXcomPalNum( path )
	return fileSize( path..PalName ) / (PalSize + 6)
end



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
			bytes = bytes..getStrChar(tmp, 5)
		end
	end
	return bytes
end



function LoadXcomFont( fileName )
	local fh = assert(io.open(fileName, "rb"))
	if not fh then
		return
	end
	
	local path, name, ext = parseFileName( fileName )
	path = path..'/'
	
	
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
	fh:close()
	
	print ("Symbols loaded: ", num)

	local origin = Origin:new(Origin.FromFile, fileName)
	font:SetOrigin(origin)
	
	return font
end



function LoadXcomImage( filename )
	local path, name, ext = parseFileName( filename )
	path = path..'/'

	local key = findAnyStringInTable( KnownImageNames[currentVersion], name )
	if key == nil then
		print ("I don't know what to do with ", filename)
	end

	local fh = assert(io.open(filename, "rb"))
	if not fh then
		return
	end
	
	local params = imageParams[currentVersion][key]
	local width = params.width
	local height = params.height
	local bufsize = width * height
	local image = ImageInfo:new()
	
	if not 	CreateXcomPalette( path.."../", params.palette, image ) then
		return
	end
	
	
	local bytes = fh:read( bufsize )
	fh:close()

	print ("Image loading...", bytes:len(), "bytes loaded")
	
	if bytes ~= nil and bytes:len() == bufsize then
		local mask = IndexMask:new()
		mask:SetMask( bytes, bufsize, width, height, -1, -1)
		
		if mask:IsOk() then
		
			image:SetImage( mask )

			local origin = Origin:new(Origin.FromFile, filename)
			image:SetOrigin(origin)
			
			return image
		else
			print("There was an error while loading "..name)
		end
		
	end
	
end



function ChangePalette(gamePath, editorId)
	local num = GetXcomPalNum( gamePath )
	
	local list = {} 
	
	for i = 1, num do
		table.insert( list, "Palette ¹"..string.char(i + 48) )
	end
	
	local selected = selectFromList( list )
	
	if selected == nil then
		print("Nothing selected")
		return
	end
	
	selected = getStrInt(selected, 9) - 49
	local palBuffer = GetXComPalette(gamePath, selected)
	
	if palBuffer ~= nil then
		local pal = Palette:new()
		if pal:Initiate( Palette.bpp8, palBuffer, Palette.sfPlain, true ) then
			setCurrentPalette( pal, editorId )
		end
	end
	
end 



function LoadLBM( filename )
	local iff = IFFLib:new()
	iff:LoadIFFFile( filename )
	
	local form = iff:FindForm("PBM ")
	
	if not form:IsOk() then
		print("PBM form not found!")
		return
	end
	
	local header = iff:FindChunk("BMHD", form)
	local colorMap = iff:FindChunk("CMAP", form)
	local body = iff:FindChunk("BODY", form)
	
	if not header:IsOk()  then
		print "BMHD not loaded!"
		return
	end
	
	if not colorMap:IsOk()  then
		print "CMAP not loaded!"
		return
	end
	
	if not body:IsOk()  then
		print "BODY not loaded!"
		return
	end
		
	local info = readDataFromBuffer( iff:ReadChunkData(header), LBMHeader )
	
	showTable(info)
	
	
	local palBuf = iff:ReadChunkData(colorMap)
	local imgBuf = iff:ReadChunkData(body)
	
	
	
	local size = info.WIDTH * info.HEIGHT
	local image = ImageInfo:new()
	local pal = Palette:new()
	
	if pal:Initiate( Palette.bpp8, palBuf, Palette.sfPlain, false ) then
		if not image:SetPalette( pal ) then
			print "loadLBM error: can't set Palette."
			return
		end
	end
	
	local origin = Origin:new(Origin.FromFile, filename)
	
	local mask = IndexMask:new()
	mask:SetMask( unpackLBMBody(imgBuf, size), size, info.WIDTH, info.HEIGHT, -1, -1)
	
	if mask:IsOk() then
		image:SetImage( mask )
		image:SetOrigin(origin)
		return image
	else
		print("loadLBM error: There was an error while initiating IndexMask")
	end
	
end
