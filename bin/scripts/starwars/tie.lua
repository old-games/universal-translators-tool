function LoadStarwarsFont()
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
