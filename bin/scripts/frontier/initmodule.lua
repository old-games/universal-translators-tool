local ModuleName = 'frontier'
local Frontier = {}
UTTModules[ModuleName] = Frontier


local gameVersions = { 'Elite 2 Frontier (DOS)' }

local ActionsOnExtension = 
{ 
	ovl = "loadOVL"
}

local currentVersion = 1

local Operations = {}







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



function Frontier.getExtensions()
	return 'el2mcga3.ovl(Font file)|el2mcga3.ovl'
end



function Frontier.openFile( fileName )
	local fileName = string.lower( fileName )
	local vol, path, name, ext = parseFileName( fileName )
	local key = ActionsOnExtension[ ext ]
	if key == nil then
		print( "Can't find function for '"..ext.."' extension" )
		return
	end
	Operations[ key ]( fileName )
end



local SymbolStruct = {}
SymbolStruct[1] =	{ BUFFER	= "DATA9" 	}
SymbolStruct[2] =	{ WIDTH 	= "BYTE" 	}




function Operations.loadOVL( filename )
	local vol, path, name, ext = parseFileName( filename )
	if name ~= "el2mcga3" then
		print "Frontier can open EL2MCGA3.OVL only!"
		return
	end

	path = vol..path..'/'

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
	
	editFont( font )
	
	fh:close()
end




print "Frontier module loaded"
