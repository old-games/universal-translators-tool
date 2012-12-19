local PalName = 'geodata/PALETTES.DAT'
local PalSize = 768
local LastPalPath = ""

currentVersion = 1

local KnownImageNames = 
{
	-- UFO1DOS 
	{ "lang", "back", "geobord", "up_bord2"},
	--	XCOM2WIN 
	{ "lang", "back", "geobord", "up_bord2"} 
}
function getKnownImageNames() return KnownImageNames[currentVersion] end

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
	
	LastPalPath = path
	
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
	
	local vol, path, name, ext = parseFileName( fileName )
	path = vol..path..'/'
	
	
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



function LoadXcomImage( path, name, key, fh )
	local params = imageParams[currentVersion][key]
	local width = params.width
	local height = params.height
	local bufsize = width * height
	local image = ImageInfo:new()
	
	if not 	CreateXcomPalette( path.."../", params.palette, image ) then
		return
	end
	
	
	local bytes = fh:read( bufsize )
	print ("Image loading...", bytes:len(), "bytes loaded")
	if bytes ~= nil and bytes:len() == bufsize then
		local mask = IndexMask:new()
		mask:SetMask( bytes, bufsize, width, height, -1, -1)
		if mask:IsOk() then
			image:SetImage( mask )
			editImage( image )
		else
			print("There was an error while loading "..name)
		end
	end
end



function ChangePalette()
	if LastPalPath:len() == 0 then
		messageBox("You must load font or image before changing palette")
		return
	end
	local num = GetXcomPalNum( LastPalPath )
	
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
	local palBuffer = GetXComPalette(LastPalPath, selected)
	if palBuffer ~= nil then
		local pal = Palette:new()
		if pal:Initiate( Palette.bpp8, palBuffer, Palette.sfPlain, true ) then
			setCurrentPalette( pal )
		end
	end
end 

