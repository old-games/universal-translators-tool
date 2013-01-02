local FNTStruct = {}
FNTStruct[1] =	{ WIDTH		= "BYTE" 	}
FNTStruct[2] =	{ HEIGHT	= "BYTE" 	}




function LoadStarwarsFont( filename )
	local path, name, ext = parseFileName( filename )

	
	local pal = Palette:new()
	if pal:Initiate( Palette.bppMono, 0, Palette.sfNone, false ) ~= true then
		print("TIE::LoadStarwarsFont:  error while setting palette")
		return
	end

	local fh = assert(io.open(filename, "rb"))
	if not fh then
		return
	end
	
	local big = string.match(name, "64") ~= nil
	local font = FontInfo:new()

	local first = readData( fh, FNTStruct )
	fh:seek("set")
	local dataSize = first.HEIGHT * 2
	
	if big then
		dataSize = first.HEIGHT * 8
	end
	
	local maxWidth = 16
	
	if big then
		maxWidth = 64
	end
	
	--- About maxWidth
	--- X-Wing and TF using fonts with mask included in
	--- so when we are loading font, we are loading full info
	--- but to FontEditor we are saying to use just half of maxWidth
	
	--- Mask of each symbol must be regenerated when exporting data back
	--- to the game.
	
	
	local maxHeight = first.HEIGHT
	font:SetValues( maxWidth / 2, maxHeight, 0, 0, 0, 7, 0, 2 )
	font:SetPalette( pal )
	
	local done = false
	while not done do
	
		local symb = readData( fh, FNTStruct )
		
		if not symb then
			break
		end
		
		local data = fh:read(dataSize)
		
		-- in 64 type fonts there something like BE - buffer must be rotated 
		-- here we are rotating only symbol data except the mask
		-- as i already said, mask must be created when exporting font
		-- to the game
		if big then
			local count = #data - 1
			for i = 0, count, 8 do
				data = swapStringBytes(data, i, i + 3, 1)
				data = swapStringBytes(data, i + 1, i + 2, 1)
			end
		end
		
		local bytes, size = unpackBitBuffer(data, 1)
		local mask = IndexMask:new()
		
		mask:SetMask( bytes, size, maxWidth / 2, maxHeight, maxWidth, maxHeight)
		
		if mask:IsOk() then
			font:AddSymbolIndexed( mask, symb.WIDTH, symb.HEIGHT )
		end
	end
	
	fh:close()
	
	local origin = Origin:new(Origin.FromFile, filename)
	font:SetOrigin( origin )
	
	return font
end

function LoadStarwarsImage()
end



local LFDStruct = {}
LFDStruct[1] =	{ ID	= "DATA4" 	}
LFDStruct[2] =	{ NAME 	= "DATA8" 	}
LFDStruct[3] =	{ SIZE 	= "DWORD" 	}



function LoadLFD( filename )
	local path, name, ext = parseFileName( filename )
	
	local fh = assert(io.open(filename, "rb"))
	if not fh then
		return
	end
	
	local done = false
	local size = fileSize( filename )
	local items = {}
	local origin = Origin:new(Origin.FromFile, filename)

	local rmap = readData( fh, LFDStruct )

	
	while not done do
		local data = readData( fh, LFDStruct )
		
		if not data then
			break
		end
		
		table.insert(items, data)
		done = fh:seek() > rmap.SIZE
	end
	local startOffset = fh:seek()
	
	fh:close()
	
	if not done then 
		return
	end
	
	local lib = LibTree:new()
	local root = lib:GetRoot()
	
	for i, current in ipairs(items) do
		
		local item = lib:AddItem( root )
		local data = LibItemData:new()
		
		data.mLibDataOffset = startOffset
		startOffset = startOffset + current.SIZE
		
		item:SetText( current.ID.." "..current.NAME )
		item:SetData( data )
	end
	
	
	lib:SetOrigin( origin )
	
	return lib
	
end
