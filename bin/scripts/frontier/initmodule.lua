local ModuleName = 'frontier'
local Frontier = {}
UTTModules[ModuleName] = Frontier


local gameVersions = { 'Elite 2 Frontier (DOS)' }

local currentVersion = 1


function Frontier.selectVersion()
	local res = selectVersionDialog( gameVersions )
	res = findStringInTable( gameVersions, res )
	if res ~= nil then
		currentVersion = res
		setModuleReady()
	end
end



function Frontier.getModuleName()
	return gameVersions[currentVersion]
end






local SymbolStruct = {}
SymbolStruct[1] =	{ BUFFER	= "DATA9" 	}
SymbolStruct[2] =	{ WIDTH 	= "BYTE" 	}




function loadOVL( filename )
	local path, name, ext = parseFileName( filename )
	if name ~= "el2mcga3" then
		print "Frontier can open EL2MCGA3.OVL only!"
		return
	end

	local pal = Palette:new()
	if pal:Initiate( Palette.bppMono, 0, Palette.sfNone, false ) ~= true then
		print("Frontier::LoadOVL:  error while setting palette")
		return
	end

	local fh = assert(io.open(filename, "rb"))
	if not fh then
		return
	end
	
	local fontStart = 24942
	local fontNum = 113
	local maxWidth = 8
	local maxHeight = 9
	
	fh:seek("set", fontStart)
	
	local font = FontInfo:new()
	font:SetValues( maxWidth, maxHeight, 0, 0, 0, 7, 0, 2 )
	font:SetPalette( pal )
	
	for i = 0, fontNum do 
		local data = readData( fh, SymbolStruct )
		local bytes, size = unpackBitBuffer(data.BUFFER, 1)
		local mask = IndexMask:new()
		mask:SetMask( bytes, size, maxWidth, maxHeight, -1, -1)
		
		if mask:IsOk() then
			font:AddSymbolIndexed( mask, data.WIDTH, maxHeight )
		end
	end
	
	fh:close()
	
	return font
end



function Frontier.ImportFont()
	local fileName = openFileDialog('el2mcga3.ovl(Font file)|el2mcga3.ovl')
	
	if fileName ~= nil then
		local font = loadOVL( fileName )
		if font ~= nil then
			editFont(font)
		end
	end
end

print "Frontier module loaded"
